#include <aosdesigner/backend/workspace.hpp>

#include <atomic>
#include <memory>
#include <boost/container/flat_map.hpp>
#include <tbb/concurrent_unordered_map.h>

#include <utilcpp/assert.hpp>
#include <utilcpp/make_unique.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/library.hpp>
#include <aosdesigner/backend/events.hpp>

#include "workspaceinternalapi.hpp"

namespace aosd {
namespace backend {

	template< class T >
	class WeakRegistry
	{
	public:
		WeakRegistry(){} // = default;

		void add( Id<T> id, std::shared_ptr<T> object )
		{
			// TODO: add some checks
			m_index.insert( std::make_pair( std::move(id), std::move(object) ) );
		}

		std::shared_ptr<T> find( const Id<T>& id ) const
		{
			auto find_it = m_index.find( id );
			if( find_it != end(m_index) )
			{
				if( auto object = find_it->second.lock() )
				{
					return object;
				} 
				// Unfortunately, tbb::concurrent_unordered_map can't erase elements safely in concurrent code, so we have to keep the null pointer.
			}

			return nullptr;
		}

	private:
		WeakRegistry( const WeakRegistry& ); // = delete;
		WeakRegistry& operator=( const WeakRegistry& ); // = delete;
		
		tbb::concurrent_unordered_map< Id<T>, std::weak_ptr<T> > m_index; 

	};

	template< class T >
	class WeakUpdateList
	{
	public:

		void add( const std::shared_ptr<T>& object )
		{
			m_update_list.emplace_back( object );
			m_update_futures.reserve( m_update_list.size() );
		}

		template< class ExecutorType, class TaskType >
		void parallel_for_all( ExecutorType&& executor, TaskType&& task )
		{
			m_update_futures.clear();
			
			for( auto it = begin(m_update_list); it != end(m_update_list); )
			{
				if( auto object = it->lock() )
				{
					m_update_futures.emplace_back( async_impl( executor, [=]{ task( object ); } ) );
					++it;
				}
				else
				{
					// we only keep weak pointers to valid elements for faster updates
					it = m_update_list.erase( it );
				}
			}

			wait_for_all( m_update_futures );
		}

	private:
		std::vector< std::weak_ptr<T> > m_update_list;
		std::vector< future<void> > m_update_futures;
	};

	using boost::container::flat_map;

	class Workspace::Impl
	{
	public:
		Impl( Workspace& workspace );

		void request_update();

		void add_to_registry( std::shared_ptr<Editor> editor ) { register_impl( editor, m_editor_registry, m_editor_update_list ); }
		void add_to_registry( std::shared_ptr<Library> library ) { register_impl( library, m_library_registry, m_library_update_list ); }
		void add_to_registry( std::shared_ptr<Sequence> sequence ) { register_impl( sequence, m_sequence_registry, m_sequence_update_list ); }

		std::shared_ptr<Project> find( const ProjectId& id ) const { return m_project_registry.find( id ); }
		std::shared_ptr<Editor> find( const EditorId& id ) const { return m_editor_registry.find( id ); }
		std::shared_ptr<Library> find( const LibraryId& id ) const { return m_library_registry.find( id ); }
		std::shared_ptr<Sequence> find( const SequenceId& id ) const { return m_sequence_registry.find( id ); }

		template< class TaskType >
		auto schedule( TaskType&& task ) -> future< decltype(task()) >;

		future<ProjectId> open_project( ProjectInfo info );
		future<void> close_project( ProjectId id );

		std::shared_ptr<Sequence> find_or_load( const SequenceId& id, const URI& location );
		std::shared_ptr<Library> find_or_load( const LibraryId& id, const URI& location );

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		friend class WorkspaceInternalAPI;

		Workspace& m_workspace;
		WorkQueue<void> m_work_queue;
		
		flat_map< ProjectId, std::shared_ptr<Project> > m_open_projects;

		WeakRegistry<Project>	m_project_registry;
		WeakRegistry<Editor>	m_editor_registry;
		WeakRegistry<Library>	m_library_registry;
		WeakRegistry<Sequence>	m_sequence_registry;

		WeakUpdateList<Project> m_project_update_list;
		WeakUpdateList<Editor> m_editor_update_list;
		WeakUpdateList<Library> m_library_update_list;
		WeakUpdateList<Sequence> m_sequence_update_list;

		std::atomic<unsigned long> m_update_request_count;


		boost::mutex m_load_library_mutex;
		boost::mutex m_load_sequence_mutex;

		void update_loop();
		void update();

		template< class T >
		void update_all( WeakUpdateList<T>& list );

		template< class T >
		void register_impl( std::shared_ptr<T> object, WeakRegistry<T>& registry, WeakUpdateList<T>& update_list )
		{
			registry.add( object->id(), object );
			schedule( [object,&update_list]{ update_list.add( object ); } );
		}

		void add_to_registry( std::shared_ptr<Project> project ) { register_impl( project, m_project_registry, m_project_update_list ); }

		SequenceInfo load_sequence_info( const URI& uri );
		LibraryInfo load_library_info( const URI& uri );

	};

	Workspace::Impl::Impl( Workspace& workspace ) 
		: m_workspace( workspace )
		, m_update_request_count( 0 )
	{

	}

	template< class TaskType >
	auto Workspace::Impl::schedule( TaskType&& task ) -> future< decltype(task()) >
	{
		auto result = async_impl( m_work_queue, std::forward<TaskType>(task) );
		m_workspace.request_update();
		return result;
	}

	void Workspace::Impl::request_update()
	{
		if( m_update_request_count > 0 )
		{
			++m_update_request_count;
		}
		else
		{
			m_workspace.async( [&]{ update_loop(); } );
		}
	}

	void Workspace::Impl::update_loop()
	{
		++m_update_request_count;
		while( m_update_request_count > 0 )
		{
			const auto request_count_on_begin = m_update_request_count.load();
			update();
			m_update_request_count -= request_count_on_begin;
		}
	}

	void Workspace::Impl::update()
	{
		m_work_queue.execute();

		update_all( m_library_update_list );
		update_all( m_sequence_update_list );
		update_all( m_editor_update_list );
		update_all( m_project_update_list );

		if( !m_work_queue.empty() )
			request_update();
	}


	template< class T >
	void Workspace::Impl::update_all( WeakUpdateList<T>& list )
	{
		auto update_task = []( std::shared_ptr<T> object ){ object->update(); };
		
		list.parallel_for_all( m_workspace.m_executor, update_task );
	}


	future<ProjectId> Workspace::Impl::open_project( ProjectInfo info )
	{
		UTILCPP_ASSERT( is_valid( info ), "Tried to open a project with invalid information!" );

		return schedule( [this,info]()-> ProjectId {
			// TODO: check that the project isn't already open

			auto project = std::make_shared<Project>( m_workspace, info );
			UTILCPP_ASSERT_NOT_NULL( project );
			UTILCPP_ASSERT( project->id() == info.id, "Project creation inconsistency!" );

			m_open_projects.insert( std::make_pair( project->id(), project ) );
			add_to_registry( project );

			event::ProjectOpen ev;
			ev.project_info = info;
			m_workspace.m_event_dispatcher.publish( project->id(), ev );

			return project->id();
		});
	}

	future<void> Workspace::Impl::close_project( ProjectId id )
	{
		UTILCPP_ASSERT( is_valid( id ), "Tried to close a project with an invalid id!" );

		return schedule( [this,id]{
			if( m_open_projects.erase( id ) )
			{
				event::ProjectClosed ev;
				ev.project_id = id;
				m_workspace.m_event_dispatcher.publish( id, ev );
			}
		});
	}

	std::shared_ptr<Sequence> Workspace::Impl::find_or_load( const SequenceId& id, const URI& location ) // TODO: refactor
	{
		boost::lock_guard<boost::mutex> lock( m_load_sequence_mutex );

		if( auto sequence = find( id ) )
			return sequence;

		auto info = load_sequence_info( location );

		if( is_valid( info ) )
		{
			auto sequence = std::make_shared<Sequence>( m_workspace, info );
			add_to_registry( sequence );
			return sequence;
		}
		
		return nullptr;
	}

	std::shared_ptr<Library> Workspace::Impl::find_or_load( const LibraryId& id, const URI& location ) // TODO: refactor
	{
		/*boost::lock_guard<boost::mutex> lock( m_load_library_mutex );

		if( auto sequence = find( id ) )
			return sequence;

		auto info = load_library_info( location );

		if( is_valid( info ) )
		{
			auto library = std::make_shared<Library>( m_workspace, info );
			add_to_registry( library );
			return library;
		}*/
		UTILCPP_NOT_IMPLEMENTED_YET;
		return nullptr;
	}

	SequenceInfo Workspace::Impl::load_sequence_info( const URI& uri )
	{
		// THIS IS TEMPORARY
		SequenceInfo info;
		info.id = make_new_id<Sequence>();
		info.name = "Unnamed Sequence";
		return info;
	}

	LibraryInfo Workspace::Impl::load_library_info( const URI& uri )
	{
		// THIS IS TEMPORARY
		LibraryInfo info;
		info.id = make_new_id<Library>();
		info.name = "Unnamed Sequence";
		return info;
	}


	///////////////////////

	Workspace::InternalAPI::InternalAPI( Workspace::Impl& workspace_impl )
		: m_workspace_impl( workspace_impl )
	{

	}

	void Workspace::InternalAPI::add_to_registry( std::shared_ptr<Sequence> sequence )
	{
		m_workspace_impl.add_to_registry( std::move(sequence) );
	}

	void Workspace::InternalAPI::add_to_registry( std::shared_ptr<Editor> editor )
	{
		m_workspace_impl.add_to_registry( std::move(editor) );
	}

	void Workspace::InternalAPI::add_to_registry( std::shared_ptr<Library> library )
	{
		m_workspace_impl.add_to_registry( std::move(library) );
	}

	std::shared_ptr<Sequence> Workspace::InternalAPI::find_or_load( const SequenceId& id, const URI& location )
	{
		return m_workspace_impl.find_or_load( id, location );
	}

	std::shared_ptr<Library> Workspace::InternalAPI::find_or_load( const LibraryId& id, const URI& location )
	{
		return m_workspace_impl.find_or_load( id, location );
	}



	///////////////////////

	Workspace::Workspace( TaskExecutor executor )
		: m_executor( std::move(executor) )
		, pimpl( std::make_unique<Impl>( *this ) )
	{

	}

	Workspace::~Workspace()
	{
		// TODO: wait for all updating to end and prevent another update
	}

	void Workspace::dispatch_events()
	{
		m_event_dispatcher.dispatch();
	}


	void Workspace::request_update()
	{
		pimpl->request_update();
	}

	Workspace::InternalAPI Workspace::internal_api()
	{
		return InternalAPI(*pimpl);
	}

	std::shared_ptr<Project> Workspace::find( const ProjectId& id ) const
	{
		return pimpl->find( id );
	}

	std::shared_ptr<Editor> Workspace::find( const EditorId& id ) const
	{
		return pimpl->find( id );
	}

	std::shared_ptr<Library> Workspace::find( const LibraryId& id ) const
	{
		return pimpl->find( id );
	}

	std::shared_ptr<Sequence> Workspace::find( const SequenceId& id ) const
	{
		return pimpl->find( id );
	}

	future<ProjectId> Workspace::open_project( ProjectInfo info )
	{
		return pimpl->open_project( info );
	}

	future<void> Workspace::close_project( ProjectId project_id )
	{
		return pimpl->close_project( project_id );
	}



}}
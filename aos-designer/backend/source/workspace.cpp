#include <aosdesigner/backend/workspace.hpp>

#include <atomic>
#include <memory>
#include <boost/container/flat_map.hpp>
#include <tbb/concurrent_unordered_map.h>

#include <utilcpp/assert.hpp>
#include <utilcpp/make_unique.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/dataprovider.hpp>
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
		Impl( Workspace& workspace, DataProvider& data_provider );

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
		future<ProjectId> open_project( URI uri );
		future<void> close_project( ProjectId id );

		DataProvider& data_provider() { return m_data_provider; }

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		friend class WorkspaceInternalAPI;

		Workspace& m_workspace;
		DataProvider& m_data_provider;
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

		void add_to_registry( std::shared_ptr<Project> project ) 
		{ 
			register_impl( std::move(project), m_project_registry, m_project_update_list ); 
		}

		ProjectId open_project_impl( const ProjectInfo& );

	};

	Workspace::Impl::Impl( Workspace& workspace, DataProvider& data_provider ) 
		: m_workspace( workspace )
		, m_data_provider( data_provider )
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

	ProjectId Workspace::Impl::open_project_impl( const ProjectInfo& project_info )
	{
		// TODO: check that the project isn't already open

		auto project = std::make_shared<Project>( m_workspace, project_info );
		UTILCPP_ASSERT_NOT_NULL( project );
		UTILCPP_ASSERT( project->id() == project_info.id, "Project creation inconsistency!" );

		m_open_projects.insert( std::make_pair( project->id(), project ) );
		add_to_registry( project );

		event::ProjectOpen ev;
		ev.project_info = project_info;
		m_workspace.m_event_dispatcher.publish( ev );

		return project->id();		
	}

	future<ProjectId> Workspace::Impl::open_project( ProjectInfo info )
	{
		UTILCPP_ASSERT( is_valid( info ), "Tried to open a project with invalid information!" );

		return schedule( [this,info]{ return open_project_impl( info ); } );
	}

	future<ProjectId> Workspace::Impl::open_project( URI uri )
	{
		return schedule( [this,uri]{
			ProjectInfo info = m_data_provider.get_project_info( uri );
			if( is_valid( info ) )
				return open_project_impl( info );
			return ProjectId(); // TODO: OR THROW AN EXCEPTION???
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
				m_workspace.m_event_dispatcher.publish( ev );
			}
		});
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

	DataProvider& Workspace::InternalAPI::data_provider()
	{
		return m_workspace_impl.data_provider();
	}

	///////////////////////

	Workspace::Workspace( TaskExecutor executor, DataProvider& data_provider )
		: m_executor( std::move(executor) )
		, pimpl( std::make_unique<Impl>( *this, data_provider ) )
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

	future<ProjectId> Workspace::open_project( URI uri )
	{
		return pimpl->open_project( uri );
	}

	future<void> Workspace::close_project( ProjectId project_id )
	{
		return pimpl->close_project( project_id );
	}



}}
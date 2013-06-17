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
#include <aosdesigner/backend/event.hpp>

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
			}

			return nullptr;
		}

	private:
		WeakRegistry( const WeakRegistry& ); // = delete;
		WeakRegistry& operator=( const WeakRegistry& ); // = delete;

		tbb::concurrent_unordered_map< Id<T>, std::weak_ptr<T> > m_index; 

	};

	using boost::container::flat_map;

	class Workspace::Impl
	{
	public:
		Impl( Workspace& workspace );
		~Impl(){} // = default

		void request_update();

		void add_to_registry( std::shared_ptr<Editor> editor ) { register_impl( editor, m_editor_registry ); }
		void add_to_registry( std::shared_ptr<Library> library ) { register_impl( library, m_library_registry ); }
		void add_to_registry( std::shared_ptr<Sequence> sequence ) { register_impl( sequence, m_sequence_registry ); }

		std::shared_ptr<Project> find( const ProjectId& id ) const { return m_project_registry.find( id ); }
		std::shared_ptr<Editor> find( const EditorId& id ) const { return m_editor_registry.find( id ); }
		std::shared_ptr<Library> find( const LibraryId& id ) const { return m_library_registry.find( id ); }
		std::shared_ptr<Sequence> find( const SequenceId& id ) const { return m_sequence_registry.find( id ); }

		template< class TaskType >
		auto schedule( TaskType&& task ) -> future< decltype(task()) >;

		future<Project&> open_project( ProjectInfo info );

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		friend class WorkspaceInternalAPI;

		Workspace& m_workspace;

		WorkQueue<void> m_work_queue;
		std::atomic<unsigned long> m_update_request_count;

		WeakRegistry<Project>	m_project_registry;
		WeakRegistry<Editor>	m_editor_registry;
		WeakRegistry<Library>	m_library_registry;
		WeakRegistry<Sequence>	m_sequence_registry;

		
		flat_map< ProjectId, std::shared_ptr<Project> > m_open_projects;

		std::vector< future<void> > m_project_update_futures;

		void update_loop();
		void update();

		template< class T >
		void register_impl( std::shared_ptr<T> object, WeakRegistry<T>& registry )
		{
			registry.add( object->id(), object );
		}

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
		
		m_project_update_futures.clear();
		m_project_update_futures.reserve( m_open_projects.size() );

		for( auto& project_slot : m_open_projects )
		{
			auto& project = project_slot.second;
			m_project_update_futures.emplace_back( m_workspace.async( [project]{ project->update(); } ) );
		}

		wait_for_all( m_project_update_futures );

		if( !m_work_queue.empty() )
			request_update();

	}

	future<Project&> Workspace::Impl::open_project( ProjectInfo info )
	{
		UTILCPP_ASSERT( is_valid( info ), "Tried to open a project with invalid information!" );

		return schedule( [this,info]()-> Project& {
			// TODO: check that the project isn't already open

			auto project = std::make_shared<Project>( m_workspace, info );
			UTILCPP_ASSERT_NOT_NULL( project );
			UTILCPP_ASSERT( project->id() == info.id, "Project creation inconsistency!" );

			m_open_projects.insert( std::make_pair( project->id(), project ) );
			m_project_registry.add( project->id(), project );

			event::ProjectOpen ev;
			ev.project_info = info;
			m_workspace.m_event_dispatcher.publish( project->id(), ev );

			return *project;
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

	future<Project&> Workspace::open_project( ProjectInfo info )
	{
		return  pimpl->open_project( info );
	}

	future<void> Workspace::close_project( ProjectId project_id )
	{
		return make_ready_future(); // TEMPORARY
	}



}}
#ifndef HGUARD_AOSD_BACKEND_WORKSPACE_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACE_HPP__

#include <functional>
#include <memory>
#include <type_traits>
#include <boost/thread/future.hpp>
#include <boost/optional/optional.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/taskexecutor.hpp>
#include <aosdesigner/backend/tools/eventdispatcher.hpp>
#include <aosdesigner/backend/tools/async.hpp>
#include <aosdesigner/backend/tools/uri.hpp>


namespace aosd {
namespace backend {

	class AOSD_BACKEND_API Workspace
	{
	public:
				
		explicit Workspace( TaskExecutor executor ); // THINK: set a default task executor?
		~Workspace();

		
		EventDispatcher::ObservationAPI& event_dispatcher() const { return m_event_dispatcher.observation_api(); }

		// Dispatch queued events to observers using the calling thread.
		void dispatch_events();
		
		void request_update();

		// project, sequence, editor, library thread-safe access - must occur in the object's update.
		template< class ObjectType, class TaskType >
		auto work_on( const Id<ObjectType>& id, TaskType task, ObjectType* dummy = nullptr ) 
			-> boost::optional< future< decltype(task(*dummy)) > >;

		//SequenceInfo get_sequence_info( SequenceId sequence_id );
		//ProjectInfo get_project_info( ProjectId project_id );
		//EditorInfo get_editeditor_info( EditorId edit_editor_id );

		//future<ProjectId> create_project();
		//future<ProjectId> open_project( URI project_address );
		//future<void> close_project( ProjectId project_id );

		class InternalAPI;
		InternalAPI internal_api();
		
	private:
		Workspace( const Workspace& ); // = delete;
		Workspace& operator=( const Workspace& ); // = delete;

		template<class T> friend class WorkspaceObject;

		TaskExecutor m_executor;
		mutable EventQueueDispatcher m_event_dispatcher;
				
		class Impl;
		std::unique_ptr<Impl> pimpl;

		template< class TaskType >
		auto async( TaskType&& task ) -> future<decltype(task())>
		{
			return async_impl( m_executor, std::forward<TaskType>(task) );
		}

		std::shared_ptr<Project> find( const ProjectId& id ) const;
		std::shared_ptr<Editor> find( const EditorId& id ) const;
		std::shared_ptr<Library> find( const LibraryId& id ) const;
		std::shared_ptr<Sequence> find( const SequenceId& id ) const;

	};

	template< class ObjectType, class TaskType >
	auto Workspace::work_on( const Id<ObjectType>& id, TaskType task, ObjectType* dummy )
		-> boost::optional< future< decltype(task(*dummy)) > >
	{
		if( auto object = find<ObjectType>( id ) )
		{
			auto& workspace_object = static_cast<WorkspaceObject&>( *object );
			return workspace_object.on_next_update( 
				[=]( ObjectType& ready_object ){
					task( ready_object );
			});
		}
		return boost::none;
	}

}}


#endif

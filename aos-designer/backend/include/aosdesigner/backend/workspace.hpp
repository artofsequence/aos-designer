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
#include <aosdesigner/backend/info/projectinfo.hpp>

namespace aosd {
namespace backend {

	class DataProvider;

	/** The Workspace is the environment in which operations on Projects can occur.
		This is the root object necessary to work with he backend.
		Workspace will keep Projects open until explicitly closed and will provide
		thread-safe access to objects like Projects, Sequences, Editors and Libraries.
		@par
		The Workspace can update the whole system either in a sequential way, each time there
		is a modification, or in a concurrent way. The way the update occurs depends on the
		provided TaskExecutor (@see TaskExecutor).

		@remark There can be several Workspace instance alive at the same time.
				Most of the time, it's not necessary to do this, but 
		
	*/
	class AOSD_BACKEND_API Workspace
	{
	public:
		
		/** Construct a Workspace which will use the provided TaskExecutor to launch update loops.
			@param executor			Task executor in which update tasks will be pushed in.
			@param data_provider	Data provider to use when in need to retrieve data from outside the backend.
		*/
		explicit Workspace( TaskExecutor executor, DataProvider& data_provider );
		~Workspace();

		/** Read-only access to the event dispatcher.
			The event dispatcher is actually a thread-safe event queue, so connections can be done 
			but no other event dispatching can be done from client code.
			@see EventQueueDispatcher

			Usage example:
			@code
				
				// global event observation:
				workspace.event_dispatcher().on<ProjectOpen>( []( const ProjectOpen& ev ){ 
					log( "Project Open: " << ev.project_indo.name );
					current_project_id = ev.project_info.id;
				});

				// observing event which source is specific to an object: 
				workspace.event_dispatcher().on<ProjectClosed>( current_project_id, []( const ProjectClosed& ev ){ 
					log( "Current project closed." );
					current_project = ProjectId::INVALID;
				});

			@endcode

			@return A special reference object which expose only the functions necessary to connect observers 
					( callable objects with the event type as attribute or no attribute ).
		*/
		EventDispatcher::ObservationAPI event_dispatcher() const { return m_event_dispatcher.observation_api(); }

		/** Dispatch queued events to observers using the calling thread.
			Usually called in an event-loop so that work being done in the Workspace
			can publish events which can be dispatched into the thread using them.
			@warning This should be called by one thread at a time.
		*/
		void dispatch_events();
		
		/** Triggers the launch of an update cycle if none is already going.
			The update cycle will occur if any task is planned by one of of the objects in the workspace.
			The update cycle will loop until no more work is to be done and will stop then.
			It is therefore not really necessary to manually call this function from client code.
			It is however called by WorkspaceObject scheduling functions, triggering the update
			each time an update cycle is not going on but tasks have been scheduled.
		*/
		void request_update();

		/** Thread-safe deferred access to backend objects.
			If the provided id refer to an object that is not registered (and therefore, not alive)
			then the task will not be executed.

			Used as follow:
			@code
				SequenceId sequence_id = sequence_to_work_on();
				workspace.work_on( sequence_id, []( Sequence& sequence ) { sequence.do_some_work(); } );
			@endcode

			The provided task will be executed into the update cycle of the target object.

			@remark As Workspace objects accessed this way queue their modifying actions to be executed
			on update cycle, remember that manipulating the object might not modify it immediately.
			If you want to wait for a modification to occur, use the .then() member in the future returned
			by the modifying member function.
						
			@tparam ObjectType	Should be either Sequence, Project, Editor or Library.
			@tparam TaskType	A task which take the target object as reference. The return type will be ignored. // TODO: replace this when optional<future<...>> is made possible
			
			@param id			Id of the target object.
			@param task			Task that will be executed in the target object's update cycle.
			@return True once the object have been found and the task have been executed, false if the object wasn't found.
		*/
		template< class ObjectType, class TaskType >
		future<bool> work_on( const Id<ObjectType>& id, TaskType task );
		
		/** Open a project for edition using the provided info.
			@remark Event published on success once done: event::ProjectOpen 

			@param info		Information of the project to open. Will be used to load the necessary data.
							The information have to be valid and the id of the project have to be unique.
			@return The id of the project once it is open.
		*/
		future<ProjectId> open_project( ProjectInfo info );
		
		/** Open a project for edition using the provided uri to retrieve the project info.
			@remark Event published on success once done: event::ProjectOpen 

			@param uri		Locate where to retrieve the project's info.
							The information have to be valid and the id of the project have to be unique.
			@return The id of the project once it is open.
		*/
		future<ProjectId> Workspace::open_project( URI uri );

		/** Close an open project (and all the related data).
			@remark Event published on success once done: event::ProjectClosed
		*/
		future<void> close_project( ProjectId project_id );

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

		template< class ObjectType > 
		static ObjectType* dummy() { return nullptr; }

	};

	template< class ObjectType, class TaskType >
	future<bool> Workspace::work_on( const Id<ObjectType>& id, TaskType task )
	{
		static_assert( std::is_base_of< WorkspaceObject<ObjectType>, ObjectType>::value, "Tried to work on an object of type unknown to Workspace! "
			"Valid types: Project, Sequence, Library, Editor" );
		if( auto object = find( id ) )
		{
			WorkspaceObject<ObjectType>& workspace_object = static_cast<WorkspaceObject<ObjectType>&>( *object );
			return workspace_object.on_next_update( [=]( ObjectType& ready_object ){ 
				task( ready_object ); 
				return true;
			});
		}

		return make_ready_future(false);
	}

}}


#endif

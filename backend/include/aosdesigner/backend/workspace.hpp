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

namespace aosd {
namespace backend {

	/** The work space in which all projects manipulations will occur.
		This is the root object to manipulate all the rest of AOS Designer's backend.
		Manage open projects, dispatch events and update everything automatically when something have changed.
		
		
	*/
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
		future<bool> work_on( const Id<ObjectType>& id, TaskType task );

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

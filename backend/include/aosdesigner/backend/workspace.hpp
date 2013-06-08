#ifndef HGUARD_AOSD_BACKEND_WORKSPACE_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACE_HPP__

#include <functional>
#include <memory>
#include <type_traits>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/taskexecutor.hpp>
#include <aosdesigner/backend/eventdispatcher.hpp>
#include <aosdesigner/backend/async.hpp>

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/uri.hpp>

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

		// TODO: project, sequence, editor, library thread-safe access - must occur in the workspace queue or async?


		//boost::future<SequenceInfo> get_sequence_info( SequenceId sequence_id );
		//boost::future<ProjectInfo> get_project_info( ProjectId project_id );
		//boost::future<EditorInfo> get_editeditor_info( EditorId edit_editor_id );

		//boost::future<ProjectId> create_project();
		//boost::future<ProjectId> open_project( URI project_address );
		//boost::future<void> close_project( ProjectId project_id );

		
		

	private:
		Workspace( const Workspace& ); // = delete;
		Workspace& operator=( const Workspace& ); // = delete;

		template<class T> friend class WorkspaceObject;

		TaskExecutor m_executor;
		mutable EventQueueDispatcher m_event_dispatcher;
		
		template< class TaskType >
		auto async( TaskType&& task ) -> boost::future<decltype(task())>
		{
			return async_impl( m_executor, std::forward<TaskType>(task) );
		}

		class Impl;
		std::unique_ptr<Impl> pimpl;

	};


}}


#endif

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

		template< class TaskType >
		auto async( TaskType&& task ) -> boost::future<decltype(task())>
		{
			return async_impl( m_executor, std::forward<TaskType>(task) );
		}

		EventQueueDispatcher& event_dispatcher() const { return m_event_dispatcher; }
		
		// TODO: project, sequence, editor, library thread-safe access - must occur in the workspace queue or async?

		// 

		

		///** Dispatch events in the calling thread. */
		void dispatch_events() { m_event_dispatcher.dispatch(); }

		//boost::future<SequenceState> get_sequence_state( SequenceId sequence_id );
		//boost::future<ProjectState> get_project_state( ProjectId project_id );
		//boost::future<EditorState> get_editeditor_state( EditorId edit_editor_id );

		//boost::future<ProjectId> create_project();
		//boost::future<ProjectId> open_project( URI project_address );
		//boost::future<void> close_project( ProjectId project_id );

		//size_t project_count() const;
		
	private:
		Workspace( const Workspace& ); // = delete;
		Workspace& operator=( const Workspace& ); // = delete;

		TaskExecutor m_executor;
		mutable EventQueueDispatcher m_event_dispatcher;

		class Impl;
		std::unique_ptr<Impl> pimpl;

		
	};


}}


#endif

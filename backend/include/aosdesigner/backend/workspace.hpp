#ifndef HGUARD_AOSD_BACKEND_WORKSPACE_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACE_HPP__

#include <functional>
#include <memory>
#include <type_traits>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/taskexecutor.hpp>
#include <aosdesigner/backend/eventdispatcher.hpp>

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
		auto schedule( TaskType task ) -> boost::future<decltype(task())>;

		EventDispatcher& event_dispatcher() { return m_event_dispatcher; }

		/////

		//void update()
		//{
		//	
		//	for( auto project : projects )
		//	{
		//		schedule( [=]{ project->update(); } );
		//		// in project update 
		//		{
		//			m_work_queue.execute();
		//			for( auto sequence : sequences )
		//			{
		//				schedule( [=]{ sequence->update(); } );
		//				// in sequence update
		//				{
		//					m_work_queue.execute();
		//					for( auto editor : editors )
		//						schedule( [=]{ editor->update(); } );
		//					// in sequence update
		//					{

		//					}
		//				}
		//			}
		//		}
		//	}
		//}

		///** Dispatch events in the calling thread. */
		//void dispatch_events() { m_event_dispatcher.dispatch(); }

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
		EventDispatcher m_event_dispatcher;

	};

	namespace detail
	{
		template< class TaskType, class ReturnType >
		void execute_task( boost::promise<ReturnType>& promise, TaskType& task )
		{
			promise.set_value( task() );
		}

		template< class TaskType >
		void execute_task( boost::promise<void>& promise, TaskType& task )
		{
			task();
			promise.set_value();
		}


	}

	template< class TaskType >
	auto Workspace::schedule( TaskType task ) -> boost::future< decltype(task()) >
	{		
		typedef decltype(task()) ResultType;

		auto promise = std::make_shared<boost::promise<ResultType>>(); // TODO: c++14 allow moving in lambda instead of having to do this
		auto result = promise->get_future();

		m_executor( [promise, task]
		{ 
			try
			{
				detail::execute_task( *promise, task );
			}
			catch( ... )
			{
				promise->set_exception( boost::current_exception() );
			}			
		});

		return std::move(result); // TODO: remove move() it is implicit but current version of VS is buggy
	}

}}


#endif

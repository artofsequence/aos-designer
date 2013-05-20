#ifndef HGUARD_AOSD_BACKEND_WORKSPACE_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACE_HPP__

#include <functional>
#include <memory>
#include <type_traits>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/taskexecutor.hpp>

namespace aosd {
namespace backend {

	

	class AOSD_BACKEND_API Workspace
	{
	public:
		
		explicit Workspace( TaskExecutor& executor ); // THINK: set a default task executor?
		~Workspace();

		template< class TaskType >
		auto schedule( TaskType task ) -> boost::future<decltype(task())>;

	private:

		TaskExecutor& m_executor;

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

		m_executor.schedule( [promise, task]
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

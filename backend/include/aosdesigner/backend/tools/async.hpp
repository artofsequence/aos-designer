#ifndef HGUARD_AOSD_BACKEND_ASYNC_HPP__
#define HGUARD_AOSD_BACKEND_ASYNC_HPP__
#pragma once

#include <memory>
#include <boost/thread/future.hpp>

namespace aosd
{
namespace backend
{
	using boost::future;
	using boost::promise;
	using boost::packaged_task;

	namespace detail_async_impl
	{
		template< class TaskType, class ReturnType >
		void execute_task( promise<ReturnType>& result, TaskType& task )
		{
			result.set_value( task() );
		}

		template< class TaskType >
		void execute_task( promise<void>& result, TaskType& task )
		{
			task();
			result.set_value();
		}
	}

	template< class ExecutorType, class TaskType >
	auto async_impl( ExecutorType&& executor, TaskType task ) -> future< decltype(task()) >
	{		
		typedef decltype(task()) ResultType;

		auto result_promise = std::make_shared<promise<ResultType>>(); // TODO: c++14 allow moving in lambda instead of having to do this
		auto result = result_promise->get_future();

		executor( [result_promise, task]
		{ 
			try
			{
				detail_async_impl::execute_task( *result_promise, task );
			}
			catch( ... )
			{
				result_promise->set_exception( boost::current_exception() );
			}			
		});

		return std::move(result); // TODO: remove move() it is implicit but current version of Boost
	}
	

}
}


#endif

#ifndef HGUARD_AOSD_BACKEND_ASYNC_HPP__
#define HGUARD_AOSD_BACKEND_ASYNC_HPP__
#pragma once

#include <memory>
#include <boost/thread/future.hpp>

namespace aosd
{
namespace backend
{
	namespace detail_async_impl
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

	template< class ExecutorType, class TaskType >
	auto async_impl( ExecutorType&& executor, TaskType task ) -> boost::future< decltype(task()) >
	{		
		typedef decltype(task()) ResultType;

		auto promise = std::make_shared<boost::promise<ResultType>>(); // TODO: c++14 allow moving in lambda instead of having to do this
		auto result = promise->get_future();

		executor( [promise, task]
		{ 
			try
			{
				detail_async_impl::execute_task( *promise, task );
			}
			catch( ... )
			{
				promise->set_exception( boost::current_exception() );
			}			
		});

		return std::move(result); // TODO: remove move() it is implicit but current version of VS is buggy
	}
	

}
}


#endif

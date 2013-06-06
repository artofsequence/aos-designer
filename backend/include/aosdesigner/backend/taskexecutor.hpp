#ifndef HGUARD_AOSD_BACKEND_TASKEXECUTOR_HPP__
#define HGUARD_AOSD_BACKEND_TASKEXECUTOR_HPP__
#pragma once

#include <functional>
#include <memory>

#include <aosdesigner/backend/api.hpp>

namespace aosd {
namespace backend {

	typedef std::function<void ()> Task;
	typedef std::function<void (Task)> TaskExecutor;

	struct TaskExecutor_Immediate
	{
		void operator()( Task task )
		{
			task();
		}
	};

	class AOSD_BACKEND_API TaskExecutor_WorkThread
	{
	public:
		TaskExecutor_WorkThread();
		~TaskExecutor_WorkThread();

		TaskExecutor_WorkThread( TaskExecutor_WorkThread&& other ); 
		TaskExecutor_WorkThread& operator=( TaskExecutor_WorkThread&& );

		void operator()( Task task );

	private:
		TaskExecutor_WorkThread( const TaskExecutor_WorkThread& ); // = delete;
		TaskExecutor_WorkThread& operator=( const TaskExecutor_WorkThread& ); // = delete;

		class Impl;
		std::unique_ptr<Impl> m_impl;
	};

	class AOSD_BACKEND_API TaskExecutor_ThreadPool
	{
	public:

	private:

	};

	class AOSD_BACKEND_API TaskExecutor_std_async
	{
	public:

	private:

	};

}
}


#endif

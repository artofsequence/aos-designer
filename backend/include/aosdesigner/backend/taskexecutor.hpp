#ifndef HGUARD_AOSD_BACKEND_TASKEXECUTOR_HPP__
#define HGUARD_AOSD_BACKEND_TASKEXECUTOR_HPP__
#pragma once


namespace aosd {
namespace backend {

	class TaskExecutor
	{
	public:
		typedef std::function<void()> Task;

		~TaskExecutor(){}

		template< class TaskType >
		void schedule( TaskType&& task ) { schedule_task( std::forward<TaskType>(task) ); }

		template< class TaskType >
		void operator()( TaskType&& task ) { schedule( std::forward<TaskType>(task) ); }

	private:
		TaskExecutor( const TaskExecutor& ); // = delete;
		TaskExecutor& operator=( const TaskExecutor& ); // = delete;

		virtual void schedule_task( Task task ) = 0;
	};



}
}


#endif

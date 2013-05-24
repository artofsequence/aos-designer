#ifndef HGUARD_AOSD_BACKEND_WORKQUEUE_HPP__
#define HGUARD_AOSD_BACKEND_WORKQUEUE_HPP__


#include <type_traits>
#include <functional>
#include <tbb/concurrent_queue.h>

namespace aosd {
namespace backend {


	template< class ContextData >
	class WorkQueue
	{
		static const ContextData* dummy() { return nullptr; }
	public:

		typedef std::function<void( const ContextData& )> WorkType;

		template< class WorkTask >
		auto push( WorkTask&& task ) -> typename std::conditional< true, void, decltype( task( *dummy()) ) >::type
		{
			m_task_queue.push( std::forward<WorkTask>(task) );
		}

		// this one allow task() to be pusshed even if there is a context data
		template< class WorkTask >
		auto push( WorkTask task ) -> typename std::conditional< true, void, decltype( task() ) >::type
		{
			m_task_queue.push( [=](const ContextData&){ task(); } );
		}


		/** Execute all the work queued until now. */
		void execute( const ContextData& context )
		{
			if( m_task_queue.empty() )
				return;

			bool end_of_work = false;
			m_task_queue.push( [&]( const ContextData& ){ end_of_work = true; } );

			WorkType work;
			while( !end_of_work && m_task_queue.try_pop( work ) )
			{
				work( context );
			}
		}

	private:

		mutable tbb::concurrent_queue< WorkType > m_task_queue;
	};

	template<>
	class WorkQueue<void>
	{
	public:

		typedef std::function<void()> WorkType;

		template< class WorkTask >
		void push( WorkTask&& task )
		{
			m_task_queue.push( std::forward<WorkTask>( task ) );
		}

		/** Execute all the work queued until now. */
		void execute()
		{
			if( m_task_queue.empty() )
				return;

			bool end_of_work = false;
			m_task_queue.push( [&](){ end_of_work = true; } );

			WorkType work;
			while( !end_of_work && m_task_queue.try_pop( work ) )
			{
				work();
			}
		}

	private:

		mutable tbb::concurrent_queue< WorkType > m_task_queue;
	};


}}


#endif

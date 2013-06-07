#include <gtest/gtest.h>

#include <aosdesigner/backend/workqueue.hpp>
#include <future>

using namespace aosd::backend;

// TODO: add some concurrent tests

TEST( Test_WorkQueue, simple_task_sequence )
{
	int k = 0;
	WorkQueue<void> work_queue;
	work_queue.push( [&]{ k = 42; } );
	work_queue.execute();
	work_queue.push( [&]{ k = 666; } );

	ASSERT_EQ( 42, k );

	work_queue.execute();

	ASSERT_EQ( 666, k );

}


TEST( Test_WorkQueue, simple_task_sequence_param )
{
	int k = 0;
	WorkQueue<int> work_queue;
	work_queue.push( [&]{ k = 42; } );
	work_queue.execute( 123 );
	work_queue.push( [&]( const int& value ){ k = value; } );

	ASSERT_EQ( 42, k );

	work_queue.execute( 666 );

	ASSERT_EQ( 666, k );

}

int TRUC = 42;
TEST( Test_WorkQueue, future_promise_shared_work )
{
	WorkQueue<void> work_queue;

	auto do_some_work = [&]()-> std::future<int*>
	{
		auto promise = std::make_shared<std::promise<int*>>();
		work_queue.push( [=]
		{
			promise->set_value( &TRUC );
		});

		return promise->get_future();
	};

	auto ft_value = do_some_work();

	work_queue.execute();

	auto value = ft_value.get();
	ASSERT_EQ( &TRUC, value );
}

TEST( Test_WorkQueue, call_simple_task_sequence )
{
	int k = 0;
	WorkQueue<void> work_queue;
	work_queue( [&]{ k = 42; } );
	work_queue.execute();
	work_queue( [&]{ k = 666; } );

	ASSERT_EQ( 42, k );

	work_queue.execute();

	ASSERT_EQ( 666, k );

}


TEST( Test_WorkQueue, call_simple_task_sequence_param )
{
	int k = 0;
	WorkQueue<int> work_queue;
	work_queue( [&]{ k = 42; } );
	work_queue.execute( 123 );
	work_queue( [&]( const int& value ){ k = value; } );

	ASSERT_EQ( 42, k );

	work_queue.execute( 666 );

	ASSERT_EQ( 666, k );

}

TEST( Test_WorkQueue, call_future_promise_shared_work )
{
	WorkQueue<void> work_queue;

	auto do_some_work = [&]()-> std::future<int*>
	{
		auto promise = std::make_shared<std::promise<int*>>();
		work_queue( [=]
		{
			promise->set_value( &TRUC );
		});

		return promise->get_future();
	};

	auto ft_value = do_some_work();

	work_queue.execute();

	auto value = ft_value.get();
	ASSERT_EQ( &TRUC, value );
}


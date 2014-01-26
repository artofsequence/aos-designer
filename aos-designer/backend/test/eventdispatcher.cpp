#include <gtest/gtest.h>

#include <boost/thread/thread.hpp>
#include <atomic>

#include <aosdesigner/backend/tools/eventdispatcher.hpp>
#include <aosdesigner/backend/events.hpp>


using namespace aosd::backend;

TEST( Test_EventDispatcher, simple_use )
{
	bool project_is_open = false;
	bool editor_began = false;

	EventDispatcher_Immediate dispatcher;
	dispatcher.on<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	dispatcher.on<event::EditorOpen>( [&]( const event::EditorOpen& ev ){ editor_began = !editor_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch( event::ProjectOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch( event::EditorOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

}


TEST( Test_EventDispatcher, simple_disconnections )
{
	bool project_is_open = false;
	bool editor_began = false;

	EventDispatcher_Immediate dispatcher;
	auto connect_a = dispatcher.on<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	auto connect_b = dispatcher.on<event::EditorOpen>( [&]( const event::EditorOpen& ev ){ editor_began = !editor_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch( event::ProjectOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	connect_a.disconnect();
	dispatcher.dispatch( event::ProjectOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch( event::EditorOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

	connect_b.disconnect();
	dispatcher.dispatch( event::EditorOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

}



TEST( Test_EventDispatcher, simple_source_observation )
{
	int all_observations_count = 0;
	
	EventDispatcher_Immediate dispatcher;
	dispatcher.on<event::SequenceAdded>( [&]{ ++all_observations_count; } );

	dispatcher.dispatch( event::SequenceAdded() );
	ASSERT_EQ( all_observations_count, 1 );
	
    dispatcher.dispatch( event::SequenceAdded() );
	ASSERT_EQ( all_observations_count, 2 );
	
}


TEST( Test_EventDispatcher, simple_use_2_threads )
{
	bool project_is_open = false;
	bool editor_began = false;
	std::atomic<bool> publishing_ended = false;

	EventDispatcher_Immediate dispatcher;

	dispatcher.on<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	dispatcher.on<event::EditorOpen>( [&]( const event::EditorOpen& ev ){ editor_began = !editor_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	auto event_publisher_thread = boost::thread::thread( [&]{
		boost::this_thread::sleep_for( boost::chrono::milliseconds(500) );
		dispatcher.dispatch( event::ProjectOpen() );
		boost::this_thread::sleep_for( boost::chrono::milliseconds(500) );
		dispatcher.dispatch( event::EditorOpen() );
		boost::this_thread::sleep_for( boost::chrono::milliseconds(300) );
		publishing_ended = true;
	});
	event_publisher_thread.detach();

	while( !publishing_ended )
	{
		boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
	}
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

}

TEST( Test_EventDispatcher, parrallel_connections )
{
	std::atomic<int> counter = 0;

	EventDispatcher_Immediate dispatcher;

	auto update_thread = boost::thread::thread( [&]{
		while( counter < 100 )
		{
			boost::this_thread::sleep_for( boost::chrono::milliseconds(8) );
			dispatcher.dispatch( event::ProjectOpen() );
		}
	});

	const auto begin_time = boost::chrono::high_resolution_clock::now();
	const auto end_time = begin_time + boost::chrono::seconds(10);

	auto check_thread = boost::thread::thread( [&]{
		while( boost::chrono::high_resolution_clock::now() < end_time )
		{
			boost::this_thread::sleep_for( boost::chrono::milliseconds(50) );
			if( counter >= 100 )
				return;
		}
		throw std::runtime_error("This test took too long!");
	});

	auto observer_thread = boost::thread::thread( [&]{
		auto observer_a = [&]{ ++counter; };
		auto observer_b = [&]{ counter += 10; };
		while( counter < 100 )
		{
			boost::this_thread::sleep_for( boost::chrono::milliseconds(50) );
			auto connect_a = dispatcher.on<event::ProjectOpen>( observer_a );
			boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
			auto connect_b = dispatcher.on<event::ProjectOpen>( observer_b );
			boost::this_thread::sleep_for( boost::chrono::milliseconds(50) );
			connect_b.disconnect();
			boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
			connect_a.disconnect();
		}
	});

	update_thread.join();
	observer_thread.join();
	check_thread.join();
}




TEST( Test_EventQueueDispatcher, simple_use )
{
	bool project_is_open = false;
	bool editor_began = false;

	EventDispatcher_Queued dispatcher;
	dispatcher.on<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	dispatcher.on<event::EditorOpen>( [&]( const event::EditorOpen& ev ){ editor_began = !editor_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.publish( event::ProjectOpen() );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.publish( event::EditorOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

}


TEST( Test_EventQueueDispatcher, simple_disconnections )
{
	bool project_is_open = false;
	bool editor_began = false;

	EventDispatcher_Queued dispatcher;
	auto connect_a = dispatcher.on<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	auto connect_b = dispatcher.on<event::EditorOpen>( [&]( const event::EditorOpen& ev ){ editor_began = !editor_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.publish( event::ProjectOpen() );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	connect_a.disconnect();
	dispatcher.publish( event::ProjectOpen() );
	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );


	dispatcher.publish( event::EditorOpen() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( editor_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

	dispatcher.publish( event::EditorOpen() );
	connect_b.disconnect();
	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

}



TEST( Test_EventQueueDispatcher, simple_source_observation )
{
	int all_observations_count = 0;

	EventDispatcher_Queued dispatcher;
	dispatcher.on<event::SequenceAdded>( [&]{ ++all_observations_count; } );
    ASSERT_EQ( all_observations_count, 0 );

	dispatcher.publish( event::SequenceAdded() );
    ASSERT_EQ( all_observations_count, 0 );
	dispatcher.dispatch();
	ASSERT_EQ( all_observations_count, 1 );

	dispatcher.publish( event::SequenceAdded() );
    ASSERT_EQ( all_observations_count, 1 );
	dispatcher.dispatch();
	ASSERT_EQ( all_observations_count, 2 );

	dispatcher.publish( event::SequenceAdded() );
    ASSERT_EQ( all_observations_count, 2 );
	dispatcher.dispatch();
	ASSERT_EQ( all_observations_count, 3 );
}

TEST( Test_EventQueueDispatcher, simple_use_2_threads )
{
	bool project_is_open = false;
	bool editor_began = false;
	std::atomic<bool> publishing_ended = false;

	EventDispatcher_Queued dispatcher;

	dispatcher.on<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	dispatcher.on<event::EditorOpen>( [&]( const event::EditorOpen& ev ){ editor_began = !editor_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( editor_began );

	auto event_publisher_thread = boost::thread::thread( [&]{
		boost::this_thread::sleep_for( boost::chrono::milliseconds(500) );
		dispatcher.publish( event::ProjectOpen() );
		boost::this_thread::sleep_for( boost::chrono::milliseconds(500) );
		dispatcher.publish( event::EditorOpen() );
		boost::this_thread::sleep_for( boost::chrono::milliseconds(300) );
		publishing_ended = true;
	});
	event_publisher_thread.detach();

	while( !publishing_ended )
	{
		boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
		dispatcher.dispatch();
	}
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( editor_began );

}

TEST( Test_EventQueueDispatcher, parrallel_connections )
{
	std::atomic<int> counter = 0;

	EventDispatcher_Queued dispatcher;

	auto update_thread = boost::thread::thread( [&]{
		while( counter < 100 )
		{
			boost::this_thread::sleep_for( boost::chrono::milliseconds(8) );
			dispatcher.publish( event::ProjectOpen() );
			dispatcher.dispatch();
		}
	});

	const auto begin_time = boost::chrono::high_resolution_clock::now();
	const auto end_time = begin_time + boost::chrono::seconds(10);

	auto check_thread = boost::thread::thread( [&]{
		while( boost::chrono::high_resolution_clock::now() < end_time )
		{
			boost::this_thread::sleep_for( boost::chrono::milliseconds(50) );
			if( counter >= 100 )
				return;
		}
		throw std::runtime_error("This test took too long!");
	});

	auto observer_thread = boost::thread::thread( [&]{
		auto observer_a = [&]{ ++counter; };
		auto observer_b = [&]{ counter += 10; };
		while( counter < 100 )
		{
			boost::this_thread::sleep_for( boost::chrono::milliseconds(50) );
			auto connect_a = dispatcher.on<event::ProjectOpen>( observer_a );
			boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
			auto connect_b = dispatcher.on<event::ProjectOpen>( observer_b );
			boost::this_thread::sleep_for( boost::chrono::milliseconds(50) );
			connect_b.disconnect();
			boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
			connect_a.disconnect();
		}
	});

	update_thread.join();
	observer_thread.join();
	check_thread.join();
}

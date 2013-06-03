#include <gtest/gtest.h>

#include <boost/thread/thread.hpp>
#include <atomic>

#include <aosdesigner/backend/eventdispatcher.hpp>
#include <aosdesigner/backend/event.hpp>


using namespace aosd::backend;

TEST( Test_EventDispatcher, simple_use )
{
	bool project_is_open = false;
	bool session_began = false;

	EventDispatcher dispatcher;
	dispatcher.connect<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	dispatcher.connect<event::SessionBegin>( [&]( const event::SessionBegin& ev ){ session_began = !session_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.publish( event::ProjectOpen() );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.publish( event::SessionBegin() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( session_began );

}


TEST( Test_EventDispatcher, simple_disconnections )
{
	bool project_is_open = false;
	bool session_began = false;

	EventDispatcher dispatcher;
	auto connect_a = dispatcher.connect<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	auto connect_b = dispatcher.connect<event::SessionBegin>( [&]( const event::SessionBegin& ev ){ session_began = !session_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.publish( event::ProjectOpen() );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( session_began );

	connect_a.disconnect();
	dispatcher.publish( event::ProjectOpen() );
	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( session_began );


	dispatcher.publish( event::SessionBegin() );
	ASSERT_TRUE( project_is_open );
	ASSERT_FALSE( session_began );

	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( session_began );

	dispatcher.publish( event::SessionBegin() );
	connect_b.disconnect();
	dispatcher.dispatch();
	ASSERT_TRUE( project_is_open );
	ASSERT_TRUE( session_began );

}



TEST( Test_EventDispatcher, simple_use_2_threads )
{
	bool project_is_open = false;
	bool session_began = false;
	std::atomic<bool> publishing_ended = false;
	
	EventDispatcher dispatcher;

	dispatcher.connect<event::ProjectOpen>( [&]{ project_is_open = !project_is_open; } );
	dispatcher.connect<event::SessionBegin>( [&]( const event::SessionBegin& ev ){ session_began = !session_began; } );
	ASSERT_FALSE( project_is_open );
	ASSERT_FALSE( session_began );

	auto event_publisher_thread = boost::thread::thread( [&]{
		boost::this_thread::sleep_for( boost::chrono::milliseconds(500) );
		dispatcher.publish( event::ProjectOpen() );
		boost::this_thread::sleep_for( boost::chrono::milliseconds(500) );
		dispatcher.publish( event::SessionBegin() );
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
	ASSERT_TRUE( session_began );

}

TEST( Test_EventDispatcher, parrallel_connections )
{
	std::atomic<int> counter = 0;

	EventDispatcher dispatcher;
	
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
			auto connect_a = dispatcher.connect<event::ProjectOpen>( observer_a );
			boost::this_thread::sleep_for( boost::chrono::milliseconds(100) );
			auto connect_b = dispatcher.connect<event::ProjectOpen>( observer_b );
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

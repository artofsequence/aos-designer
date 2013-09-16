#include <gtest/gtest.h>

#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/workspace.hpp>

#include <aoslcpp/algorithm/edition.hpp>

#include "dataprovider.hpp"

using namespace aosd::backend;

namespace {
	DummyDataProvider data_provider;
	TaskExecutor_Immediate executor;

}

TEST( Test_Sequence, basic_usage )
{
	Workspace workspace( executor, data_provider );
	
	SequenceInfo info;
	info.id = make_new_id<Sequence>();
	info.name = "Test Sequence";

	auto check_basic_state = [&]( const Sequence& s )
	{
		ASSERT_EQ( info.id, s.id() );
		ASSERT_TRUE( is_valid( s.id() ) );

		const auto s_info = s.info();
		ASSERT_TRUE( is_valid( s_info ) );

		const auto s_aosl = s.aosl_source();
		SequenceId s_id = to_id<Sequence>( s_aosl.id() );
		ASSERT_TRUE( is_valid( s_id ) );
		ASSERT_EQ( s_id, info.id );
		ASSERT_EQ( s_id, s.id() );
	};

	Sequence s_a( workspace, info );
	check_basic_state( s_a );
	
	const auto a_story = aoslcpp::make_empty_sequence( "Hello, World!", "1234", "in_the_beginning" );
	Sequence s_b( workspace, info, a_story );
	check_basic_state( s_b );

}

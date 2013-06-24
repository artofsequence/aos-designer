#include <gtest/gtest.h>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/sequence.hpp>

#include "dataprovider.hpp"

using namespace aosd::backend;

namespace {
	DummyDataProvider data_provider;
	TaskExecutor_Immediate executor;

}

TEST( Test_Editor, basic_usage )
{
	Workspace workspace( executor, data_provider );

	SequenceInfo sequence_info;
	sequence_info.id = make_new_id<Sequence>();
	sequence_info.aosl_location = "blahblah";
	sequence_info.name = "Dummy Sequence";
	auto sequence = std::make_shared<Sequence>( workspace, sequence_info, data_provider.get_aosl_sequence( sequence_info.aosl_location ) );

	EditorInfo info;
	info.id = make_new_id<Editor>();
	info.sequence_id = sequence->id();

	Editor editor( workspace, info, sequence );
	ASSERT_TRUE( is_valid( editor.info() ) );
	ASSERT_EQ( info.id, editor.id() );
	ASSERT_EQ( info.id, editor.info().id );
	ASSERT_EQ( sequence_info.id, editor.info().sequence_id );

}


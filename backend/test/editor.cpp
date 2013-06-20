#include <gtest/gtest.h>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/editor.hpp>

using namespace aosd::backend;

TEST( Test_Editor, basic_usage )
{
	TaskExecutor_Immediate executor;
	Workspace workspace( executor );

	EditorInfo info;
	info.id = make_new_id<Editor>();
	info.project_id = make_new_id<Project>();
	info.sequence_id = make_new_id<Sequence>();

	Editor editor( workspace, info );
	ASSERT_TRUE( is_valid( editor.info() ) );
	ASSERT_EQ( info.id, editor.id() );
	ASSERT_EQ( info.id, editor.info().id );

}


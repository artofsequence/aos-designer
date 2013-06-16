#include <gtest/gtest.h>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/project.hpp>

using namespace aosd::backend;

TEST( Test_Workspace, access_object )
{
	TaskExecutor_Immediate executor;
	Workspace workspace( executor );
	
	bool accessed_nonexisting_project = false;
	auto access_done = workspace.work_on( make_new_id<Project>(), [&]( Project& project ){ accessed_nonexisting_project = true; } );
	ASSERT_FALSE( accessed_nonexisting_project );
	ASSERT_FALSE( access_done.get() );

	// TODO: find a way to test if you can access an object that do exists

}

#include <gtest/gtest.h>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/event.hpp>

using namespace aosd::backend;

TEST( Test_Workspace, access_project_failure )
{
	TaskExecutor_Immediate executor;
	Workspace workspace( executor );
	
	bool accessed_nonexisting_project = false;
	auto access_done = workspace.work_on( make_new_id<Project>(), [&]( Project& project ){ accessed_nonexisting_project = true; } );
	ASSERT_FALSE( accessed_nonexisting_project );
	ASSERT_FALSE( access_done.get() );
	
}

TEST( Test_Workspace, open_project )
{
	TaskExecutor_Immediate executor;
	Workspace workspace( executor );

	ProjectInfo project_info;
	project_info.id = make_new_id<Project>();
	project_info.name = "Unnamed project";
	
	bool got_the_global_message = false;
	bool got_the_specific_message = false;
	workspace.event_dispatcher().on<event::ProjectOpen>( [&]{ got_the_global_message = true; } );
	workspace.event_dispatcher().on<event::ProjectOpen>( project_info.id, [&]{ got_the_specific_message = true; } );

	workspace.open_project( project_info );
	workspace.dispatch_events();
	ASSERT_TRUE( got_the_global_message );
	ASSERT_TRUE( got_the_specific_message );

	bool accessed_project = false;
	auto access_done = workspace.work_on( project_info.id, [&]( Project& project ){ 
		ASSERT_EQ( project_info.id, project.id() );
		accessed_project = true;
	});

	ASSERT_TRUE( accessed_project );
	ASSERT_TRUE( access_done.get() );

}


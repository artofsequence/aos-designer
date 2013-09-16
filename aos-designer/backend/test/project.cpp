#include <gtest/gtest.h>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/project.hpp>

#include "dataprovider.hpp"

using namespace aosd::backend;

namespace {
	DummyDataProvider data_provider;
	TaskExecutor_Immediate executor;

}


TEST( Test_Project, basic_usage )
{
	Workspace workspace( executor, data_provider );

	ProjectInfo project_info;
	project_info.id = make_new_id<Project>();
	project_info.name = "Unnamed project";
	
	Project project( workspace, project_info );
	ASSERT_TRUE( is_valid( project.info() ) );
	ASSERT_EQ( project_info.id, project.id() );
	ASSERT_EQ( project_info.id, project.info().id );

}


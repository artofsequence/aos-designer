#include <gtest/gtest.h>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/project.hpp>

using namespace aosd::backend;

TEST( Test_Workspace, access_object )
{
	Workspace workspace( (TaskExecutor_Immediate()) );
	
	bool accessed_nonexisting_project = false;
	auto opt_ft = workspace.work_on( make_new_id<Project>(), [&]( Project& project ){ accessed_nonexisting_project = true; } );
	ASSERT_FALSE( accessed_nonexisting_project );
	ASSERT_FALSE( opt_ft.is_initialized() );

	// TODO: find a way to test if you can access an object that do exists

}

//
//#include <boost/optional.hpp>
//#include <future>
//
//boost::optional< std::future<void> > top() { return std::async( []{ int i=0; ++i;  } ); }
//
//int main()
//{
//	auto opt = top();
//}

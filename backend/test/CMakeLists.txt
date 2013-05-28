cmake_minimum_required( VERSION 2.8 )


set( AOSD_BACKEND_TEST_SOURCES
	id.cpp
)
source_group( "\\" FILES ${AOSD_BACKEND_TEST_SOURCES} )

include_directories( ${GTEST_INCLUDE_DIR} )

add_executable( test-aosdesigner-backend ${AOSD_BACKEND_TEST_SOURCES} )
target_link_libraries( test-aosdesigner-backend 
	gtest 
	gtest_main
	aosdesigner-backend
)
set_property( TARGET test-aosdesigner-backend PROPERTY FOLDER ${AOS_TEST_PROJECTS_GROUP_PATH} )

add_test( NAME test-aosdesigner-backend
	WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
	COMMAND test-aosdesigner-backend
)


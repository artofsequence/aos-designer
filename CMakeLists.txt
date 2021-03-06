cmake_minimum_required( VERSION 2.8.11 )

project( AOS_Designer )


set( BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/Build )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR} )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR} )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR} )

#####################################################
# Common configuration.

set( AOS_TEST_PROJECTS_GROUP_PATH tests-aos
	CACHE STRING 
	"Name of the virtual directory that will contain all AOS test projects."
	FORCE 
)

# Of course we want unit tests possible.
enable_testing()

# Allow generating test projects if the user want it.
option( AOS_FORCE_ENABLE_ALL_TESTS "Enable by force generation of all test projects of AOS projects" ON )
option( AOS_FORCE_DISABLE_ALL_TESTS "Disable by force generation of all test projects of AOS projects (this option have priority)" OFF )

macro( AOS_FORCE_ENABLE_TEST_ALL_PROJECTS ON_OR_OFF )
	set( UTILCPP_ENABLE_TESTS 	${ON_OR_OFF}  	CACHE BOOL "" FORCE )
	set( AOSLCPP_ENABLE_TESTS 	${ON_OR_OFF} 	CACHE BOOL "" FORCE )
	set( AOSD_ENABLE_ALL_TESTS 	${ON_OR_OFF} 	CACHE BOOL "" FORCE )
#	message( "UTILCPP_ENABLE_TESTS: ${UTILCPP_ENABLE_TESTS}" )
#	message( "AOSLCPP_ENABLE_TESTS: ${AOSLCPP_ENABLE_TESTS}" )
#	message( "AOSD_ENABLE_ALL_TESTS: ${AOSD_ENABLE_ALL_TESTS}" )
endmacro()

if( AOS_FORCE_ENABLE_ALL_TESTS AND NOT AOS_FORCE_DISABLE_ALL_TESTS )
	AOS_FORCE_ENABLE_TEST_ALL_PROJECTS( ON )
endif()

if( AOS_FORCE_DISABLE_ALL_TESTS )
	AOS_FORCE_ENABLE_TEST_ALL_PROJECTS( OFF )
endif()


#####################################################
# Projects.

add_subdirectory( dependencies )
add_subdirectory( aosl )
add_subdirectory( utilcpp )
add_subdirectory( aosl-cpp )
add_subdirectory( aos-designer )


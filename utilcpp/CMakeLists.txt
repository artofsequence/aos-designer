cmake_minimum_required( VERSION 2.8.11 )

# set( BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/Build )

# set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR} )
# set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR} )
# set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR} )


set( AOS_TEST_PROJECTS_GROUP_PATH aos-tests 
	CACHE STRING 
	"Name of the virtual directory that will contain all AOS test projects."
	FORCE 
)

# Of course we want unit tests possible.
enable_testing()

# Allow generating test projects if the user want it.
option( AOS_FORCE_ENABLE_ALL_TESTS "Enable by force generation of all test projects of AOS projects" OFF )
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


#-----------------------------------------------

project( UtilCPP )

# Important directories :
set( UTILCPP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( UTILCPP_INCLUDE_DIR ${UTILCPP_ROOT_DIR}/include )

set( UTILCPP_HEADERS_DIR ${UTILCPP_INCLUDE_DIR}/utilcpp )
set( UTILCPP_SOURCE_DIR ${UTILCPP_ROOT_DIR}/sources )

set( UTILCPP_CMAKE_DIR ${UTILCPP_ROOT_DIR}/cmake )

# CMake utilities for C++
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UTILCPP_CMAKE_DIR} )

set( UTILCPP_CMAKE_DIR ${UTILCPP_CMAKE_DIR}
	CACHE PATH "Directories containing CMake utilisies." FORCE )

include( utilcpp_projects )
UTILCPP_USE_BOOST()

# Add dependencies projects to make thhem visible from IDEs
add_subdirectory( dependencies )

#--------------------------------------------
# UTILCPP source files

# headers
set( UTILCPP_HEADERS
	${UTILCPP_HEADERS_DIR}/hardconfig.hpp
	${UTILCPP_HEADERS_DIR}/assert.hpp
	${UTILCPP_HEADERS_DIR}/log.hpp
	${UTILCPP_HEADERS_DIR}/platforminfo.hpp
	${UTILCPP_HEADERS_DIR}/moduleapi.hpp
	${UTILCPP_HEADERS_DIR}/make_unique.hpp
	${UTILCPP_HEADERS_DIR}/move_on_copy.hpp
)

# sources
set( UTILCPP_SOURCES
	${UTILCPP_SOURCE_DIR}/log.cpp
)

# all source files
set( UTILCPP_ALL_FILES
	${UTILCPP_HEADERS}
	${UTILCPP_SOURCES}
)

# Grouping
source_group( utilcpp FILES ${UTILCPP_ALL_FILES} )

# Make sure required include directories will be available for compilation
set( UTILCPP_INCLUDE_DIR ${UTILCPP_INCLUDE_DIR}
	CACHE PATH "Directories to include in projects using UtilCPP" FORCE
)

# Generate the library
UTILCPP_MAKE_LIBRARY( utilcpp STATIC 
	SOURCES ${UTILCPP_ALL_FILES}
)

# Add the test projects if wanted
option( UTILCPP_ENABLE_TESTS "Enable generating test projects for this project." OFF )
if( UTILCPP_ENABLE_TESTS )
	add_subdirectory( test )
endif()

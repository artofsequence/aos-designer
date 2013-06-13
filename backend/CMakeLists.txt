cmake_minimum_required( VERSION 2.8.11 )

project( aosdesigner-backend )

####################################################
# Dependencies.

# Boost
UTILCPP_USE_BOOST(
	system
	date_time
	chrono
	thread
	filesystem
)

# TBB

if( NOT DEFINED TBB_INCLUDE_DIRS )
	set( TBB_INCLUDE_DIRS "TBB_INCLUDE_DIRS-NOT-SET" CACHE PATH "Location of the Intel TBB include directory." FORCE )
	message( FATAL_ERROR "AOS Designer back-end requires Intel TBB but it's include directory 'TBB_INCLUDE_DIRS' was NOT FOUND!\nMake sure the 'tbb' target library is available too!" )
endif()

include_directories( ${TBB_INCLUDE_DIRS} )

#####################################################
# Directories.


set( AOSD_BACKEND_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( AOSD_BACKEND_INCLUDE_DIR ${AOSD_BACKEND_INCLUDE_DIR} PARENT_SCOPE )

set( AOSD_BACKEND_API_DIR ${AOSD_BACKEND_INCLUDE_DIR}/aosdesigner/backend )
set( AOSD_BACKEND_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source )

set( AOSD_BACKEND_API_RESOURCE_DIR ${AOSD_BACKEND_API_DIR}/resource )
set( AOSD_BACKEND_API_TOOLS_DIR ${AOSD_BACKEND_API_DIR}/tools )

set( AOSD_BACKEND_RESOURCE_SOURCE_DIR ${AOSD_BACKEND_SOURCE_DIR}/resource )


#####################################################
# API Header files.

set( AOSD_BACKEND_API_ROOT_HEADERS
	${AOSD_BACKEND_API_DIR}/id.hpp
	${AOSD_BACKEND_API_DIR}/event.hpp
	${AOSD_BACKEND_API_DIR}/workspace.hpp
	${AOSD_BACKEND_API_DIR}/workspaceobject.hpp
	${AOSD_BACKEND_API_DIR}/project.hpp
	${AOSD_BACKEND_API_DIR}/sequence.hpp
	${AOSD_BACKEND_API_DIR}/projectinfo.hpp
	${AOSD_BACKEND_API_DIR}/sequenceinfo.hpp
	${AOSD_BACKEND_API_DIR}/library.hpp
	${AOSD_BACKEND_API_DIR}/libraryinfo.hpp
	${AOSD_BACKEND_API_DIR}/editor.hpp
	${AOSD_BACKEND_API_DIR}/editorinfo.hpp
)

set( AOSD_BACKEND_API_TOOLS_HEADERS
	${AOSD_BACKEND_API_TOOLS_DIR}/eventdispatcher.hpp
	${AOSD_BACKEND_API_TOOLS_DIR}/workqueue.hpp
	${AOSD_BACKEND_API_TOOLS_DIR}/async.hpp
	${AOSD_BACKEND_API_TOOLS_DIR}/taskexecutor.hpp
	${AOSD_BACKEND_API_TOOLS_DIR}/uri.hpp
)


set( AOSD_BACKEND_API_RESOURCE_HEADERS
	${AOSD_BACKEND_API_RESOURCE_DIR}/resource.hpp
	${AOSD_BACKEND_API_RESOURCE_DIR}/resourceptr.hpp
	${AOSD_BACKEND_API_RESOURCE_DIR}/resourceref.hpp
	${AOSD_BACKEND_API_RESOURCE_DIR}/resourceprovider.hpp
	${AOSD_BACKEND_API_RESOURCE_DIR}/resourcefactory.hpp
	${AOSD_BACKEND_API_RESOURCE_DIR}/resourceinfo.hpp
	
)

set( AOSD_BACKEND_API_HEADERS
	${AOSD_BACKEND_API_ROOT_HEADERS}
	${AOSD_BACKEND_API_TOOLS_HEADERS}
	${AOSD_BACKEND_API_RESOURCE_HEADERS}
)

#####################################################
# All non-api source/header files.

set( AOSD_BACKEND_ROOT_SOURCES
	${AOSD_BACKEND_SOURCE_DIR}/id.cpp
	${AOSD_BACKEND_SOURCE_DIR}/workspace.cpp
	${AOSD_BACKEND_SOURCE_DIR}/project.cpp
	${AOSD_BACKEND_SOURCE_DIR}/sequence.cpp
	${AOSD_BACKEND_SOURCE_DIR}/editor.cpp
	${AOSD_BACKEND_SOURCE_DIR}/library.cpp
)


set( AOSD_BACKEND_RESOURCE_SOURCES
	${AOSD_BACKEND_RESOURCE_SOURCE_DIR}/resource.cpp
	${AOSD_BACKEND_RESOURCE_SOURCE_DIR}/resourceprovider.cpp
	${AOSD_BACKEND_RESOURCE_SOURCE_DIR}/resourcefactory.cpp
)

set( AOSD_BACKEND_SOURCES
	${AOSD_BACKEND_ROOT_SOURCES}
	${AOSD_BACKEND_RESOURCE_SOURCES}
)

#####################################################
# Files groups.

source_group( "\\backend_api" FILES ${AOSD_BACKEND_API_ROOT_HEADERS} )
source_group( "\\backend_api\\tools" FILES ${AOSD_BACKEND_API_TOOLS_HEADERS} )
source_group( "\\backend_api\\resource" FILES ${AOSD_BACKEND_API_RESOURCE_HEADERS} )
source_group( "\\backend_sources" FILES ${AOSD_BACKEND_ROOT_SOURCES} )
source_group( "\\backend_sources\\resource" FILES ${AOSD_BACKEND_RESOURCE_SOURCES} )

####################################################
# Bind them all together.

UTILCPP_MAKE_LIBRARY( aosdesigner-backend SHARED
	API_HEADERS_DIR
		${AOSD_BACKEND_API_DIR}
	API_DEFINE
		AOSD_BACKEND_API
	SOURCES
		${AOSD_BACKEND_API_HEADERS} 
		${AOSD_BACKEND_SOURCES}
	INCLUDE_DIRS
		${AOSD_BACKEND_INCLUDE_DIR}
		${AOSLCPP_INCLUDE_DIRS}
		${TBB_INCLUDE_DIRS}
	LINK_TARGETS
		aoslcpp
	DEPENDENCIES
		tbb
)

# We need the AOSL definition file in the build directory
add_custom_command( TARGET aosdesigner-backend POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy ${AOSL_XSD_FILE} ${AOSDESIGNER_BUILD_DIR}
) 

add_custom_command( TARGET aosdesigner-backend POST_BUILD 
	COMMAND python ${AOSDESIGNER_ROOT_DIR}/script/post_build.py 
		${AOSDESIGNER_BUILD_MODE}
		${AOSDESIGNER_BUILD_DIR}
)

# Add the test projects if wanted
option( AOSD_BACKEND_ENABLE_TESTS "Enable generating test projects for this project." OFF )

if( AOSD_BACKEND_ENABLE_TESTS OR AOSD_ENABLE_ALL_TESTS )
	add_subdirectory( test )
endif()

cmake_minimum_required( VERSION 2.8 )

project( AOS_Designer )

#####################################################
# Common configuration.

if( MSVC )
	 # Deactivate warnings
	 set( WARNINGS_TO_DISABLE
		4251 # We assume that all binaries will be compiled with the same compiler version.
		4996
	 )
	 set( MSVC_WARNING_DISABLED )
	 message( STATUS "Disabling MSVC Warnings : " )
	 foreach( warning_number ${WARNINGS_TO_DISABLE} )
		message( STATUS " -> C" ${warning_number} )
		set( MSVC_WARNING_DISABLED "${MSVC_WARNING_DISABLED} /wd${warning_number}" )
	 endforeach()
	 set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_WARNING_DISABLED}" )
	 
else() # We assume that other compilers will have GCC interface/
	 # Update if necessary
	 # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

# Force Boost.Thread V4 use for all projects, including dependencies.
add_definitions( -DBOOST_THREAD_VERSION=4 )

# Use UtilCPP CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UTILCPP_CMAKE_DIR} )

set( AOSDESIGNER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

# Current build mode
set( AOSDESIGNER_BUILD_MODE "$(Configuration)" ) #until I find a cross-platform way to get the configuration...

# Target build dir
set( AOSDESIGNER_BUILD_DIR ${BUILD_DIR}/${AOSDESIGNER_BUILD_MODE} )

#####################################################
# Projects.

add_subdirectory( backend )
add_subdirectory( frontend-qt ) # TODO: make it optional
add_subdirectory( aosdesigner )

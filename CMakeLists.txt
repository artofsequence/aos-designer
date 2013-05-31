cmake_minimum_required( VERSION 2.8 )

project( AOS_Designer )

#####################################################
# Common configuration.

# Use UtilCPP CMake modules
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UTILCPP_CMAKE_DIR} )
include( utilcpp_projects )

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


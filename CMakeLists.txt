cmake_minimum_required( VERSION 2.8 )

project( AOS_Designer )

add_subdirectory( backend )
add_subdirectory( frontend-qt ) # TODO: make it optional

#####################################################
# Sub-directories.
set( AOSDESIGNER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

# Current build mode
set( AOSDESIGNER_BUILD_MODE "$(Configuration)" ) #until I find a cross-platform way to get the configuration...

# Target build dir
set( AOSDESIGNER_BUILD_DIR ${BUILD_DIR}/${AOSDESIGNER_BUILD_MODE} )

#####################################################

set( AOSDESIGNER_SOURCES
	${AOSDESIGNER_ROOT_DIR}/application.hpp
	${AOSDESIGNER_ROOT_DIR}/paths.hpp
	${AOSDESIGNER_ROOT_DIR}/main.cpp
	${AOSDESIGNER_ROOT_DIR}/application.cpp
	${AOSDESIGNER_ROOT_DIR}/paths.cpp
)

###################################################

# File grouping
source_group( "\\" FILES ${AOSDESIGNER_SOURCES} )
source_group( "\\_cmake" FILES CMakeLists.txt )

####################################################
# Bind them all together.

# All the compiled sources.
set( AOSDESIGNER_ALL_SOURCES
	${AOSDESIGNER_SOURCES}
	CMakeLists.txt
)

include_directories(
	${AOSDESIGNER_BACKEND_INCLUDE_DIR}
	${AOSDESIGNER_FRONTEND_QT_INCLUDE_DIR} # TODO: will be optional
	${AOSLCPP_INCLUDE_DIRS}
	${UTILCPP_INCLUDE_DIR}
)

add_executable( aosdesigner ${AOSDESIGNER_ALL_SOURCES} )
target_link_libraries( aosdesigner
	${Boost_LIBRARIES}
	aosdesigner-backend
	aosdesigner-frontend-qt
	utilcpp 
	aoslcpp
)

# We need the AOSL definition file in the build directory
add_custom_command( TARGET aosdesigner POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy ${AOSL_XSD_FILE} ${AOSDESIGNER_BUILD_DIR}
) 

add_custom_command( TARGET aosdesigner POST_BUILD 
	COMMAND python ${AOSDESIGNER_ROOT_DIR}/script/post_build.py 
		${AOSDESIGNER_BUILD_MODE} 
		${AOSDESIGNER_BUILD_DIR} 
)

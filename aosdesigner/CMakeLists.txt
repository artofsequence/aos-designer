cmake_minimum_required( VERSION 2.8 )

#####################################################
# Sub-directories.
set( AOSDESIGNER_SOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources )

#####################################################

set( AOSDESIGNER_SOURCES
	${AOSDESIGNER_SOURCES_DIR}/application.hpp
	${AOSDESIGNER_SOURCES_DIR}/main.cpp
	${AOSDESIGNER_SOURCES_DIR}/application.cpp
)


####################################################
# Bind them all together.


UTILCPP_MAKE_EXECUTABLE( aosdesigner
	SOURCES
		${AOSDESIGNER_SOURCES}
	INCLUDE_DIRS
		${AOSDESIGNER_BACKEND_INCLUDE_DIR}
		${AOSDESIGNER_FRONTEND_QT_INCLUDE_DIR} # TODO: will be optional
		${AOSLCPP_INCLUDE_DIRS}
	LINK_TARGETS
		aoslcpp
		aosdesigner-backend
		aosdesigner-frontend-qt
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

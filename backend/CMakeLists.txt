cmake_minimum_required( VERSION 2.8 )

project( aosdesigner-backend )

####################################################
# Dependencies.

# Boost

if( WIN32 ) 
	# On Windows: check that the right boost binaries are set before continuing
	if( NOT DEFINED BOOST_LIBRARYDIR OR BOOST_LIBRARYDIR STREQUAL "BOOST_LIBRARYDIR-NOT-SET" )
		set( BOOST_LIBRARYDIR "BOOST_LIBRARYDIR-NOT-SET" CACHE PATH "Location of the Boost library binaries" FORCE )
		message( FATAL_ERROR "BOOST_LIBRARYDIR is not set. Before continuing, please set it to the correct binary path (depending on if you want to link with 32 or 64bit version)." )
	endif()
	
endif()


set( Boost_USE_STATIC_LIBS        ON )
set( Boost_USE_MULTITHREADED      ON )
set( Boost_USE_STATIC_RUNTIME    OFF )
find_package( Boost REQUIRED COMPONENTS 
	date_time 
	filesystem 
	system
	chrono
	thread
	program_options
)
if( NOT Boost_FOUND )
	message( SEND_ERROR "AOS Designer requires Boost libraries, NOT FOUND!" )
endif()

include_directories( ${Boost_INCLUDE_DIR} )

#####################################################
# Directories.


set( AOSD_BACKEND_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( AOSD_BACKEND_INCLUDE_DIR ${AOSD_BACKEND_INCLUDE_DIR} PARENT_SCOPE )

set( AOSD_BACKEND_HEADER_DIR ${AOSD_BACKEND_INCLUDE_DIR}/aosdesigner/backend )
set( AOSD_BACKEND_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source )

#####################################################
# Header files.

set( AOSD_BACKEND_ROOT_HEADERS
	${AOSD_BACKEND_HEADER_DIR}/api.hpp
	${AOSD_BACKEND_HEADER_DIR}/workspace.hpp
	${AOSD_BACKEND_HEADER_DIR}/context.hpp
	${AOSD_BACKEND_HEADER_DIR}/project.hpp
	${AOSD_BACKEND_HEADER_DIR}/sequence.hpp
	${AOSD_BACKEND_HEADER_DIR}/sequenceid.hpp
	${AOSD_BACKEND_HEADER_DIR}/projectinfos.hpp
	${AOSD_BACKEND_HEADER_DIR}/sequenceinfos.hpp
	${AOSD_BACKEND_HEADER_DIR}/library.hpp
	${AOSD_BACKEND_HEADER_DIR}/paths.hpp
)

set( AOSD_BACKEND_EDITION_HEADERS
	${AOSD_BACKEND_HEADER_DIR}/editionsession.hpp
	${AOSD_BACKEND_HEADER_DIR}/editionsessionid.hpp
	${AOSD_BACKEND_HEADER_DIR}/editionsessioninfos.hpp
)

set( AOSD_BACKEND_RESOURCE_HEADERS
	${AOSD_BACKEND_HEADER_DIR}/resource.hpp
	${AOSD_BACKEND_HEADER_DIR}/resourceptr.hpp
	${AOSD_BACKEND_HEADER_DIR}/resourceref.hpp
	${AOSD_BACKEND_HEADER_DIR}/resourceprovider.hpp
	${AOSD_BACKEND_HEADER_DIR}/resourcefactory.hpp
	${AOSD_BACKEND_HEADER_DIR}/resourceinfo.hpp
	${AOSD_BACKEND_HEADER_DIR}/uri.hpp
)

set( AOSD_BACKEND_HEADERS
	${AOSD_BACKEND_ROOT_HEADERS}
	${AOSD_BACKEND_EDITION_HEADERS}
	${AOSD_BACKEND_RESOURCE_HEADERS}
)

#####################################################
# Source files.

set( AOSD_BACKEND_ROOT_SOURCES
	${AOSD_BACKEND_SOURCE_DIR}/workspace.cpp	
	${AOSD_BACKEND_SOURCE_DIR}/context.cpp
	${AOSD_BACKEND_SOURCE_DIR}/project.cpp
	${AOSD_BACKEND_SOURCE_DIR}/sequence.cpp
	${AOSD_BACKEND_SOURCE_DIR}/library.cpp
	${AOSD_BACKEND_SOURCE_DIR}/paths.cpp
)

set( AOSD_BACKEND_EDITION_SOURCES
	${AOSD_BACKEND_SOURCE_DIR}/editionsession.cpp
	${AOSD_BACKEND_SOURCE_DIR}/editionsessionId.cpp
)

set( AOSD_BACKEND_RESOURCE_SOURCES
	${AOSD_BACKEND_SOURCE_DIR}/resource.cpp
	${AOSD_BACKEND_SOURCE_DIR}/resourceprovider.cpp
	${AOSD_BACKEND_SOURCE_DIR}/resourcefactory.cpp
)

set( AOSD_BACKEND_SOURCES
	${AOSD_BACKEND_ROOT_SOURCES}
	${AOSD_BACKEND_EDITION_SOURCES}
	${AOSD_BACKEND_RESOURCE_SOURCES}
)

#####################################################
# Files groups.

source_group( "\\backend" FILES ${AOSD_BACKEND_ROOT_HEADERS} ${AOSD_BACKEND_ROOT_SOURCES} )
source_group( "\\backend\\edition" FILES ${AOSD_BACKEND_EDITION_HEADERS} ${AOSD_BACKEND_EDITION_SOURCES} )
source_group( "\\backend\\resource" FILES ${AOSD_BACKEND_RESOURCE_HEADERS} ${AOSD_BACKEND_RESOURCE_SOURCES} )
source_group( "\\_cmake" FILES CMakeLists.txt )

####################################################
# Bind them all together.

# All the files of the project.
set( AOSD_BACKEND_ALL_FILES 
	${AOSD_BACKEND_HEADERS} 
	${AOSD_BACKEND_SOURCES} 
	CMakeLists.txt 
)

include_directories( 
	${AOSD_BACKEND_INCLUDE_DIR}
	${AOSLCPP_INCLUDE_DIRS}
	${UTILCPP_INCLUDE_DIR}
)

# Symbol import/export: this project code will export symbols, while 
add_definitions( -DAOSD_BACKEND_EXPORT )

add_library( aosdesigner-backend SHARED ${AOSD_BACKEND_ALL_FILES} )
target_link_libraries( aosdesigner-backend
	${Boost_LIBRARIES}
	utilcpp
	aoslcpp
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

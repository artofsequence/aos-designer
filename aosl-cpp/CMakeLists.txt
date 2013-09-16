cmake_minimum_required ( VERSION 2.8.11 )


project( AOSL-CPP )

# Dependencies:

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UTILCPP_CMAKE_DIR} )
include( utilcpp_projects )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake )

UTILCPP_USE_BOOST(
	date_time 
	filesystem
	system 
	chrono
)

find_package( XSD )
if( NOT XSD_FOUND )
	message( SEND_ERROR "AOSL-CPP requires XSD/Tree library, NOT FOUND! See " )
endif()



# Important directories :
set( AOSLCPP_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( AOSLCPP_INCLUDE_DIR ${AOSLCPP_ROOT_DIR}/include )

set( AOSLCPP_HEADERS_DIR ${AOSLCPP_INCLUDE_DIR}/aoslcpp )
set( AOSLCPP_SOURCE_DIR ${AOSLCPP_ROOT_DIR}/source )

set( AOSLCPP_ALGORITHM_HEADERS_DIR ${AOSLCPP_HEADERS_DIR}/algorithm )
set( AOSLCPP_ALGORITHM_SOURCES_DIR ${AOSLCPP_SOURCE_DIR}/algorithm )

set( AOSLCPP_AOSL_HEADERS_DIR ${AOSLCPP_INCLUDE_DIR}/aosl )
set( AOSLCPP_AOSL_SOURCES_DIR ${AOSLCPP_SOURCE_DIR}/aosl )

set( AOSLCPP_SCRIPT_DIR script )


#--------------------------------------------
# AOSL generated files:
# Get only the generated headers...
file( GLOB_RECURSE AOSLCPP_AOSL_HEADERS 
	${AOSLCPP_AOSL_HEADERS_DIR}/*.hpp
)
file( GLOB_RECURSE AOSLCPP_AOSL_INLINES 
	${AOSLCPP_AOSL_HEADERS_DIR}/*.inl
)

# Get only the generated sources...
file( GLOB_RECURSE AOSLCPP_AOSL_SOURCES 
	${AOSLCPP_AOSL_SOURCES_DIR}/*.cpp
)

#--------------------------------------------
# AOSLCPP original (not generated) files

#### Headers 

# algorithms headers
set( AOSLCPP_ALGORITHM_HEADERS
	${AOSLCPP_ALGORITHM_HEADERS_DIR}/algorithm.hpp
	${AOSLCPP_ALGORITHM_HEADERS_DIR}/find.hpp
	${AOSLCPP_ALGORITHM_HEADERS_DIR}/for_each.hpp
	${AOSLCPP_ALGORITHM_HEADERS_DIR}/execution.hpp
	${AOSLCPP_ALGORITHM_HEADERS_DIR}/edition.hpp
	${AOSLCPP_ALGORITHM_HEADERS_DIR}/iterator.hpp
)

# tool types headers
set( AOSLCPP_TOOL_HEADERS
	${AOSLCPP_HEADERS_DIR}/common.hpp
	
	${AOSLCPP_HEADERS_DIR}/sequenceInterpreter.hpp
	${AOSLCPP_HEADERS_DIR}/storyPath.hpp
	${AOSLCPP_HEADERS_DIR}/canvasState.hpp
	${AOSLCPP_HEADERS_DIR}/navigationState.hpp
	
)

# all original headers
set( AOSLCPP_ORIGINAL_HEADERS
	${AOSLCPP_ALGORITHM_HEADERS}
	${AOSLCPP_TOOL_HEADERS}	
)

#### Sources

# algorithm sources
set( AOSLCPP_ALGORITHM_SOURCES
	${AOSLCPP_ALGORITHM_SOURCES_DIR}/find.cpp
	${AOSLCPP_ALGORITHM_SOURCES_DIR}/execution.cpp
	${AOSLCPP_ALGORITHM_SOURCES_DIR}/edition.cpp
	${AOSLCPP_ALGORITHM_SOURCES_DIR}/iterator.cpp
)


# tool types sources
set( AOSLCPP_TOOL_SOURCES
	${AOSLCPP_SOURCE_DIR}/common.cpp

	${AOSLCPP_SOURCE_DIR}/sequenceInterpreter.cpp
	${AOSLCPP_SOURCE_DIR}/storyPath.cpp
	${AOSLCPP_SOURCE_DIR}/canvasState.cpp
	${AOSLCPP_SOURCE_DIR}/navigationState.cpp
	
)

set( AOSLCPP_ORIGINAL_SOURCES
	${AOSLCPP_ALGORITHM_SOURCES}
	${AOSLCPP_TOOL_SOURCES}
)

#### All 

# all algorithms files
set( AOSLCPP_ALGORITHM_ALL_FILES 
	${AOSLCPP_ALGORITHM_HEADERS}
	${AOSLCPP_ALGORITHM_SOURCES}
)

# all tools files
set( AOSLCPP_TOOL_ALL_FILES 
	${AOSLCPP_TOOL_HEADERS}
	${AOSLCPP_TOOL_SOURCES}
)


# all original files
set( AOSLCPP_ORIGINAL_ALL_FILES
	${AOSLCPP_ORIGINAL_HEADERS}
	${AOSLCPP_ORIGINAL_SOURCES}
)


#--------------------------------------------
# verify that we did get the generated files
set( AOSLCPP_AOSL_ALL_FILES 
        ${AOSLCPP_AOSL_HEADERS} 
        ${AOSLCPP_AOSL_INLINES}
        ${AOSLCPP_AOSL_SOURCES}
    )
list( LENGTH AOSLCPP_AOSL_ALL_FILES AOSLCPP_AOSL_FILES_COUNT )

message( "Found AOSLCPP source files count = " ${AOSLCPP_AOSL_FILES_COUNT} )

if( ${AOSLCPP_AOSL_FILES_COUNT} EQUAL 0 )

	# no aosl files found! 
	message( FATAL_ERROR "Couldn't find AOSL aosl source files! Use scripts to generate the sources!" )
	
endif()

#--------------------------------------------

# Get all headers...
set( AOSLCPP_HEADERS 
	${AOSLCPP_ORIGINAL_HEADERS}
	${AOSLCPP_AOSL_HEADERS}
	${AOSLCPP_AOSL_INLINES}
)

# Get all sources...
set( AOSLCPP_SOURCES 
	${AOSLCPP_ORIGINAL_SOURCES}
	${AOSLCPP_AOSL_SOURCES}
)

# Make sure the generated code is isolated in a separate virtual folder in IDEs supporting them
source_group( aosl 					FILES ${AOSLCPP_AOSL_HEADERS}   	)
source_group( aosl\\inline 			FILES ${AOSLCPP_AOSL_INLINES} 		)
source_group( aosl\\source 			FILES ${AOSLCPP_AOSL_SOURCES} 		)
source_group( aoslcpp\\algorithm	FILES ${AOSLCPP_ALGORITHM_ALL_FILES})
source_group( aoslcpp 				FILES ${AOSLCPP_TOOL_ALL_FILES} 	)

# Make sure required include directories will be available for compilation
set( AOSLCPP_INCLUDE_DIRS ${AOSLCPP_INCLUDE_DIR} ${XSD_INCLUDE_DIR} 
	CACHE STRING "Directories to include in projects using AOSL-CPP" FORCE
)

UTILCPP_MAKE_LIBRARY( aoslcpp STATIC
	SOURCES 
		${AOSLCPP_SOURCES}
		${AOSLCPP_HEADERS}
	LINK_TARGETS
		${XERCESC_LIBRARY}
	INCLUDE_DIRS 
		${AOSLCPP_INCLUDE_DIR}
		${XSD_INCLUDE_DIR}
)


# Add the test projects if wanted
option( AOSLCPP_ENABLE_TESTS "Enable generating test projects for this project." OFF )
if( AOSLCPP_ENABLE_TESTS )
	add_subdirectory( test )
endif()

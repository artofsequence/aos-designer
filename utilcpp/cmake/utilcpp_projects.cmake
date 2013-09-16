include( cmakeconfig )
include( cmakeutils )

if( MSVC ) # VS2012 doesn't support correctly the tuples yet
	add_definitions( /D _VARIADIC_MAX=10 )
endif()

# Make sure we use UNICODE.
add_definitions(-DUNICODE -D_UNICODE)


# Use relative paths
# This is mostly to reduce path size for command-line limits on windows
if( WIN32 )

	DebugLog( STATUS "Using relative paths (where possible) ..." )
	# This seems to break Xcode projects so definitely don't enable on Apple builds
	set( CMAKE_USE_RELATIVE_PATHS 			TRUE	CACHE BOOL "It is preferable to use relative paths on Windows compilers." )
	set( CMAKE_SUPPRESS_REGENERATION 		TRUE	CACHE BOOL "Not sure what is this feature. Option taken from OGRE." )

	if( MSVC )
		# force multi-thread compilation on Visual Studio
		set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP" )
		DebugLog( "Forced Visual Studio to allow parallel compilations (/MP). \n    Flags : " ${CMAKE_CXX_FLAGS} )
	endif()
  
endif()


macro( UTILCPP_USE_BOOST )
	
	if( WIN32 ) 
		# On Windows: check that the right boost binaries are set before continuing
		if( NOT DEFINED BOOST_LIBRARYDIR OR BOOST_LIBRARYDIR STREQUAL "BOOST_LIBRARYDIR-NOT-SET" )
			set( BOOST_LIBRARYDIR "BOOST_LIBRARYDIR-NOT-SET" CACHE PATH "Location of the Boost library binaries" FORCE )
			message( FATAL_ERROR "BOOST_LIBRARYDIR is not set. Before continuing, please set it to the correct binary path (depending on if you want to link with 32 or 64bit version)." )
		endif()
		
	endif()
	
	# Force Boost.Thread V4 use for all projects, including dependencies.
	add_definitions( -DBOOST_THREAD_VERSION=4 -DBOOST_RESULT_OF_USE_DECLTYPE )

	set( Boost_USE_STATIC_LIBS        ON )
	set( Boost_USE_MULTITHREADED      ON )
	set( Boost_USE_STATIC_RUNTIME    OFF )
	find_package( Boost 1.54.0 REQUIRED COMPONENTS ${ARGV} )
	
	if( NOT Boost_FOUND )
		message( SEND_ERROR "AOS Designer requires Boost libraries, NOT FOUND!" )
	endif()

	include_directories( ${Boost_INCLUDE_DIR} )

endmacro()

macro( UTILCPP_PRE_SETUP_PROJECT project_name )
	PARSE_ARGUMENTS( ARG "SOURCES;INCLUDE_DIRS" "" ${ARGV} )
	# ARG_SOURCES		: list of source files
	# ARG_INCLUDE_DIRS	: list of directories with headers used by this project
	
	list( LENGTH ARG_INCLUDE_DIRS includ_dirs_count )
	
	# In case we want to edit the project alone.
	project( ${project_name} )
	
	
	if( MSVC )
		 # Deactivate warnings
		 set( WARNINGS_TO_DISABLE
			4251 # We assume that all binaries will be compiled with the same compiler version.
			4996
		 )
		 set( MSVC_WARNING_DISABLED )
		 DebugLog( STATUS "Disabling MSVC Warnings : " )
		 foreach( warning_number ${WARNINGS_TO_DISABLE} )
			DebugLog( STATUS " -> C" ${warning_number} )
			set( MSVC_WARNING_DISABLED "${MSVC_WARNING_DISABLED} /wd${warning_number}" )
		 endforeach()
		 set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MSVC_WARNING_DISABLED}" )
		 
	else() # We assume that other compilers will have GCC interface/
		 # Update if necessary
		 # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
	endif()

	include_directories( ${UTILCPP_INCLUDE_DIR} )
		
	if( includ_dirs_count GREATER 0 )
		include_directories( ${ARG_INCLUDE_DIRS} )
	else()
		DebugLog( "No additional include directories!" )
	endif()
		
	
	source_group( "\\" FILES ${ARG_SOURCES} )
		
	# Make sure we can edit the CMakeLists.txt file from the editor.
	set( ARG_SOURCES ${ARG_SOURCES} CMakeLists.txt )
	source_group( "\\_cmake" FILES CMakeLists.txt )
	# TODO: if not all editors works with that, just make sure it is not inserted.
	
	# UTILCPP_DETECT_MEMORY_LEAK()
	

endmacro()

macro( UTILCPP_POST_SETUP_PROJECT project_name )
	PARSE_ARGUMENTS( ARG "LINK_TARGETS;DEPENDENCIES" "" ${ARGV} )
	# ARG_LINK_TARGETS	: list of projects to link to
	# ARG_DEPENDENCIES	: list of our projects that this project rely on 
	
	list( LENGTH ARG_LINK_TARGETS link_targets_count )
	list( LENGTH ARG_DEPENDENCIES dependencies_count )
	
	# Link with boost libraries if they are declared.
	if( Boost_LIBRARIES )
		set( ARG_LINK_TARGETS ${ARG_LINK_TARGETS} ${Boost_LIBRARIES} )
	endif()
	
	if( NOT project_name STREQUAL "utilcpp" )
		set( ARG_LINK_TARGETS ${ARG_LINK_TARGETS} utilcpp )
	endif()
		
	if( link_targets_count EQUAL 0 )
		DebugLog( "No additional external libraries linked to this one!" )
	else()
		DebugLog( "Adding " ${ARG_LINK_TARGETS} " as link targets." )
		target_link_libraries( ${project_name} ${ARG_LINK_TARGETS} )
	endif()
	
	if( dependencies_count EQUAL 0 )
		DebugLog( "No additional dependencies to this one!" )
	else()
		DebugLog( "Adding " ${ARG_DEPENDENCIES} " as dependencies." )
		add_dependencies( ${project_name} ${ARG_DEPENDENCIES} )
	endif()
		

endmacro()

macro( UTILCPP_MAKE_EXECUTABLE project_name )
	PARSE_ARGUMENTS( ARG "SOURCES;LINK_TARGETS;DEPENDENCIES;INCLUDE_DIRS" "CONSOLE" ${ARGV} )
	# ARG_SOURCES		: list of source files
	# ARG_LINK_TARGETS	: list of projects to link to
	# ARG_DEPENDENCIES	: list of our projects that this project rely on 
	# ARG_INCLUDE_DIRS	: list of directories with headers used by this project
	# ARG_CONSOLE 		: if set, the executable can show a console.
	
	message( STATUS "-- Executable : " ${project_name} " --" )
	DebugLog(
		"\n    Target Name : ${project_name}"
		"\n    SOURCES : ${ARG_SOURCES}" 
		"\n    LINK TARGETS : ${ARG_LINK_TARGETS}" 
		"\n    DEPENDENCIES : ${ARG_DEPENDENCIES}" 
		"\n    INCLUDE DIRECTORIES : ${ARG_INCLUDE_DIRS}" 
		"\n    GUI MODE : ${CONSOLE}"
	)
	
	# Special instruction to not display the console and automatically link with the 
	# os libraries that allow GUI display.
	if( NOT ARG_CONSOLE )
		if( WIN32 )
			set( GUI_TYPE WIN32 )
		else()
			set( GUI_TYPE MACOSX_BUNDLE )
		endif()
	else()
		set( GUI_TYPE )
	endif()
	
	UTILCPP_PRE_SETUP_PROJECT( ${project_name}
		SOURCES ${ARG_SOURCES}
		INCLUDE_DIRS ${ARG_INCLUDE_DIRS}		
	)
	
	# Now we are ready for generating the project:
	add_executable( ${project_name} ${GUI_TYPE}
		# provided source files
		${ARG_SOURCES} 
	)
	
	UTILCPP_POST_SETUP_PROJECT( ${project_name} 
		LINK_TARGETS ${ARG_LINK_TARGETS}
		DEPENDENCIES ${ARG_DEPENDENCIES}
	)
		
	message( STATUS "-- Executable : " ${project_name} " - DONE --\n" )
	
endmacro()

macro( UTILCPP_MAKE_LIBRARY project_name )
	PARSE_ARGUMENTS( ARG "SOURCES;LINK_TARGETS;DEPENDENCIES;INCLUDE_DIRS;API_HEADERS_DIR;API_DEFINE" "STATIC;MODULE" ${ARGV} )
	# ARG_SOURCES		: list of source files
	# ARG_LINK_TARGETS	: list of projects to link to
	# ARG_DEPENDENCIES	: list of our projects that this project rely on 
	# ARG_INCLUDE_DIRS	: list of directories with headers used by this project
	# ARG_API_HEADERS_DIR		: directory where the API headers are set
	# ARG_API_DEFINE	: API define to use in C++
	
	if( ${ARG_STATIC} )
		set( library_mode STATIC )
	elseif( ${ARG_MODULE} )
		set( library_mode MODULE )
	else()
		# By default, all NetRush libraries are compile-time dynamic link library.
		set( library_mode SHARED )
	endif()
	
	list( LENGTH ARG_API_HEADERS_DIR project_api_dir_count )
	if( project_api_dir_count GREATER 1 )
		message( SEND_ERROR "Project " ${project_name} " : too much api dirs (API_HEADERS_DIR) defined! Only 1 or 0 required!" )
	endif()
	
	message( STATUS "-- Library : " ${project_name} " (" ${library_mode} ") --" )
	DebugLog(
		"\nTarget Name : " ${project_name}
		"\n    SOURCES : " ${ARG_SOURCES} 
		"\n    LINK TARGETS : " ${ARG_LINK_TARGETS}
		"\n    DEPENDENCIES : " ${ARG_DEPENDENCIES}
		"\n    INCLUDE DIRECTORIES : " ${ARG_INCLUDE_DIRS}
	)
	
	string(	TOUPPER ${project_name} BIG_PROJECT_NAME ) 
	string( REPLACE "-" "_" BIG_PROJECT_NAME ${BIG_PROJECT_NAME} )
	
	if( NOT ARG_API_DEFINE )
		set( ARG_API_DEFINE ${BIG_PROJECT_NAME}_API )
	endif()
	
	# If it is not already present (or if we are forced by the user)
	# we generate a header file in the local directory that will provide
	# the ${BIG_PROJECT_NAME}_API C/C++ macro used to mark exported/imported
	# functions and classes.

	set( PROJECT_API_HEADER_NAME ${UTILCPP_PROJECT_API_HEADER_NAME} )
	if( project_api_dir_count EQUAL 1 )
		file( TO_CMAKE_PATH ${ARG_API_HEADERS_DIR} ARG_API_HEADERS_DIR )
		set( PROJECT_API_HEADER_NAME ${ARG_API_HEADERS_DIR}/${PROJECT_API_HEADER_NAME} )
	endif()	
	file( TO_CMAKE_PATH ${PROJECT_API_HEADER_NAME} PROJECT_API_HEADER_PATH )
	
	if( UTILCPP_FORCE_GENERATE_LIBRARIES_API OR NOT EXISTS ${PROJECT_API_HEADER_PATH} )
		if( ${ARG_STATIC} )
			set( API_HEADER_TEMPLATE ${UTILCPP_STATIC_API_HEADER_TEMPLATE} )
		else()
			set( API_HEADER_TEMPLATE ${UTILCPP_PROJECT_API_HEADER_TEMPLATE} )
		endif()
	
		DebugLog( "Generating " ${PROJECT_API_HEADER_PATH} " (from " ${API_HEADER_TEMPLATE} " ) ..." )
		configure_file( ${API_HEADER_TEMPLATE} ${PROJECT_API_HEADER_PATH} )
		
		DebugLog( "Generation done." )
	endif()

	# Make sure the API functions and classes (marked with ${BIG_PROJECT_NAME}_API)
	# are exported when it is this project's code that is compiled,
	# imported otherwise.
	# See the api.hpp file generation.
	set( API_EXPORT_DEFINE "-D${BIG_PROJECT_NAME}_EXPORT" )
	DebugLog( "Adding compilation args : ${API_EXPORT_DEFINE}" )
	add_definitions( ${API_EXPORT_DEFINE} ) 
	
	set( ARG_SOURCES
		# Automatically adding the generated api file in the project (to make it visible).
		${PROJECT_API_HEADER_NAME} 
		# provided source files
		${ARG_SOURCES}
	)
	
	UTILCPP_PRE_SETUP_PROJECT( ${project_name}
		SOURCES ${ARG_SOURCES}
		INCLUDE_DIRS ${ARG_INCLUDE_DIRS}		
	)
	
	# Now we are ready for generating the project:
	add_library( ${project_name} ${library_mode}
		${ARG_SOURCES}
	)
	
	UTILCPP_POST_SETUP_PROJECT( ${project_name} 
		LINK_TARGETS ${ARG_LINK_TARGETS}
		DEPENDENCIES ${ARG_DEPENDENCIES}
	)
	
	message( STATUS "-- Library : " ${project_name} " - DONE --\n" )

endmacro()

macro( UTILCPP_MAKE_TEST_FOR project_name )
	PARSE_ARGUMENTS( ARG "SOURCES;LINK_TARGETS;DEPENDENCIES;INCLUDE_DIRS" "" ${ARGV} )
	
	set( test_name test-${project_name} )
	
	source_group( "\\" FILES ${ARG_SOURCES} )
	
	UTILCPP_MAKE_EXECUTABLE( ${test_name}
		SOURCES
			${ARG_SOURCES}
		INCLUDE_DIRS 
			${ARG_INCLUDE_DIRS}
			${GTEST_INCLUDE_DIR}
		LINK_TARGETS 
			${ARG_LINK_TARGETS}
			gtest
			gtest_main
			${project_name}
		DEPENDENCIES
			${ARG_DEPENDENCIES}
		CONSOLE # all tests are console applications
	)
	
	add_test( NAME ${test_name}
		WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
		COMMAND ${test_name}
	)
	
	ProjectGroup( ${AOS_TEST_PROJECTS_GROUP_PATH} PROJECTS ${test_name} )
	
endmacro()


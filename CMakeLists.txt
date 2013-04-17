cmake_minimum_required( VERSION 2.8 )

project( AOS_Designer )

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

# We need Qt as GUI library.
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
find_package( Qt5Widgets REQUIRED )

#####################################################
# Sub-directories.
set( AOSDESIGNER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( AOSDESIGNER_CORE_DIR ${AOSDESIGNER_ROOT_DIR}/core )
set( AOSDESIGNER_VIEW_DIR ${AOSDESIGNER_ROOT_DIR}/view )
set( AOSDESIGNER_RC_DIR ${AOSDESIGNER_VIEW_DIR}/rc )
set( AOSDESIGNER_UI_DIR ${AOSDESIGNER_VIEW_DIR}/ui )
set( AOSDESIGNER_DIALOG_DIR ${AOSDESIGNER_VIEW_DIR}/dialog )

set( AOSDESIGNER_CORE_RESOURCES_DIR ${AOSDESIGNER_CORE_DIR}/resources )

set( AOSDESIGNER_VIEW_MODEL_DIR ${AOSDESIGNER_VIEW_DIR}/model )
set( AOSDESIGNER_VIEW_EDITOR_DIR ${AOSDESIGNER_VIEW_DIR}/editor )
set( AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR ${AOSDESIGNER_VIEW_EDITOR_DIR}/canvas )
set( AOSDESIGNER_VIEW_EDITOR_STORY_DIR ${AOSDESIGNER_VIEW_EDITOR_DIR}/story )

# Current build mode
set( AOSDESIGNER_BUILD_MODE "$(Configuration)" ) #until I find a cross-platform way to get the configuration...

# Target build dir
set( AOSDESIGNER_BUILD_DIR ${BUILD_DIR}/${AOSDESIGNER_BUILD_MODE} )

#####################################################
# Header files.

# Application header files.
set( AOSDESIGNER_APPLICATION_HEADERS
	${AOSDESIGNER_ROOT_DIR}/Application.hpp
	${AOSDESIGNER_ROOT_DIR}/Paths.hpp
)

#-----------------------------------------------------------------

# Core objects header files.
set( AOSDESIGNER_CORE_HEADERS
	${AOSDESIGNER_CORE_DIR}/context.hpp
	${AOSDESIGNER_CORE_DIR}/project.hpp
	${AOSDESIGNER_CORE_DIR}/sequence.hpp
	${AOSDESIGNER_CORE_DIR}/sequenceid.hpp
	${AOSDESIGNER_CORE_DIR}/projectinfos.hpp
	${AOSDESIGNER_CORE_DIR}/sequenceinfos.hpp
	${AOSDESIGNER_CORE_DIR}/editionsession.hpp
	${AOSDESIGNER_CORE_DIR}/editionsessionid.hpp
	${AOSDESIGNER_CORE_DIR}/library.hpp
)

# Resources system header files.
set( AOSDESIGNER_CORE_RESOURCES_HEADERS
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resource.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourceptr.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourceref.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourceprovider.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourcefactory.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourceinfo.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/uri.hpp
)


#-----------------------------------------------------------------



# Views header files.
set( AOSDESIGNER_VIEW_HEADERS
	${AOSDESIGNER_VIEW_DIR}/applicationview.hpp
	${AOSDESIGNER_VIEW_DIR}/mainwindow.hpp
	${AOSDESIGNER_VIEW_DIR}/projectview.hpp
	${AOSDESIGNER_VIEW_DIR}/sequencelistView.hpp
	${AOSDESIGNER_VIEW_DIR}/librariesview.hpp
	${AOSDESIGNER_VIEW_DIR}/changesview.hpp
	${AOSDESIGNER_VIEW_DIR}/objectsview.hpp
	${AOSDESIGNER_VIEW_DIR}/layersview.hpp
	${AOSDESIGNER_VIEW_DIR}/toolboxview.hpp
	${AOSDESIGNER_VIEW_DIR}/logview.hpp
	${AOSDESIGNER_VIEW_DIR}/dialogs.hpp
	${AOSDESIGNER_VIEW_DIR}/designeractions.hpp
	${AOSDESIGNER_VIEW_DIR}/editiontoolview.hpp
	${AOSDESIGNER_VIEW_DIR}/freewindow.hpp
	${AOSDESIGNER_VIEW_DIR}/freewindowmanager.hpp
)   


# Dialog header files.
set( AOSDESIGNER_DIALOG_HEADERS
	${AOSDESIGNER_DIALOG_DIR}/welcomescreen.hpp
	${AOSDESIGNER_DIALOG_DIR}/newprojectdialog.hpp
	${AOSDESIGNER_DIALOG_DIR}/newsequencedialog.hpp
	${AOSDESIGNER_DIALOG_DIR}/neweditionsessiondialog.hpp
)

# View-model header files.
set( AOSDESIGNER_VIEW_MODEL_HEADERS
	${AOSDESIGNER_VIEW_MODEL_DIR}/canvasobjectsmodel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/canvaslayersmodel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/layerobjectsmodel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/lastchangesmodel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/librarymodel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/modelviewbinder.hpp
)


# Canvas editor views header files.
set( AOSDESIGNER_VIEW_EDITOR_CANVAS_HEADERS
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/canvasview.hpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/canvasgraphicsview.hpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/canvasinvisibleobjectsview.hpp
)

# Story editor views header files.
set( AOSDESIGNER_VIEW_EDITOR_STORY_HEADERS
	${AOSDESIGNER_VIEW_EDITOR_STORY_DIR}/storyview.hpp
)

# Editor views header files.
set( AOSDESIGNER_VIEW_EDITOR_HEADERS
	${AOSDESIGNER_VIEW_EDITOR_DIR}/editormanager.hpp
	${AOSDESIGNER_VIEW_EDITOR_DIR}/editor.hpp
)

#-----------------------------------------------------------------

# All header files.
set( AOSDESIGNER_ALL_HEADERS  
	${AOSDESIGNER_APPLICATION_HEADERS}
	${AOSDESIGNER_CORE_HEADERS}
	${AOSDESIGNER_CORE_RESOURCES_HEADERS}
	${AOSDESIGNER_VIEW_HEADERS}
	${AOSDESIGNER_DIALOG_HEADERS}
	${AOSDESIGNER_VIEW_MODEL_HEADERS}
	${AOSDESIGNER_VIEW_EDITOR_HEADERS}
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_HEADERS}
	${AOSDESIGNER_VIEW_EDITOR_STORY_HEADERS}
)

# Headers that depends on QObject
set( AOSDESIGNER_QOBJECT_HEADERS
	${AOSDESIGNER_ALL_HEADERS}
)
 

# Header files needs to be processed by Qt's pre-processor to generate Moc files.
qt5_wrap_cpp( AOSDESIGNER_QOBJECT_HEADERS_MOC ${AOSDESIGNER_QOBJECT_HEADERS} )

# Group generated files in the same isolated virtual directory.
source_group( generated\\moc FILES ${AOSDESIGNER_QOBJECT_HEADERS_MOC} )


#####################################################
# Source files.

# Application source files.
set( AOSDESIGNER_APPLICATION_SOURCES
	${AOSDESIGNER_ROOT_DIR}/main.cpp
	${AOSDESIGNER_ROOT_DIR}/application.cpp
	${AOSDESIGNER_ROOT_DIR}/paths.cpp
)


# Views source files.
set( AOSDESIGNER_VIEW_SOURCES 
	${AOSDESIGNER_VIEW_DIR}/applicationview.cpp
	${AOSDESIGNER_VIEW_DIR}/mainWindow.cpp
	${AOSDESIGNER_VIEW_DIR}/projectview.cpp
	${AOSDESIGNER_VIEW_DIR}/sequencelistview.cpp
	${AOSDESIGNER_VIEW_DIR}/librariesview.cpp
	${AOSDESIGNER_VIEW_DIR}/logview.cpp
	${AOSDESIGNER_VIEW_DIR}/objectsview.cpp
	${AOSDESIGNER_VIEW_DIR}/layersview.cpp
	${AOSDESIGNER_VIEW_DIR}/toolboxview.cpp
	${AOSDESIGNER_VIEW_DIR}/changesview.cpp
	${AOSDESIGNER_VIEW_DIR}/dialogs.cpp
	${AOSDESIGNER_VIEW_DIR}/designeractions.cpp
	${AOSDESIGNER_VIEW_DIR}/editiontoolview.cpp
	${AOSDESIGNER_VIEW_DIR}/freewindowmanager.cpp
	${AOSDESIGNER_VIEW_DIR}/freewindow.cpp
)   


# Dialog source files.
set( AOSDESIGNER_DIALOG_SOURCES 
	${AOSDESIGNER_DIALOG_DIR}/welcomescreen.cpp
	${AOSDESIGNER_DIALOG_DIR}/newprojectdialog.cpp
	${AOSDESIGNER_DIALOG_DIR}/newsequencedialog.cpp
	${AOSDESIGNER_DIALOG_DIR}/neweditionsessiondialog.cpp
)


# View-model source files.
set( AOSDESIGNER_VIEW_MODEL_SOURCES 
	${AOSDESIGNER_VIEW_MODEL_DIR}/canvasobjectsmodel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/canvaslayersmodel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/layerobjectsmodel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/lastchangesmodel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/librarymodel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/modelviewbinder.cpp
)

# Canvas editor views source files.
set( AOSDESIGNER_VIEW_EDITOR_CANVAS_SOURCES
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/canvasview.cpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/canvasgraphicsView.cpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/canvasinvisibleobjectsview.cpp
)

# Story editor views source files.
set( AOSDESIGNER_VIEW_EDITOR_STORY_SOURCES
	${AOSDESIGNER_VIEW_EDITOR_STORY_DIR}/storyview.cpp
)


# Editor views source files.
set( AOSDESIGNER_VIEW_EDITOR_SOURCES 
	${AOSDESIGNER_VIEW_EDITOR_DIR}/editor.cpp
    ${AOSDESIGNER_VIEW_EDITOR_DIR}/editormanager.cpp
)
	
#------------------------------------------------------

# Core source files
set( AOSDESIGNER_CORE_SOURCES
	${AOSDESIGNER_CORE_DIR}/context.cpp
	${AOSDESIGNER_CORE_DIR}/project.cpp
	${AOSDESIGNER_CORE_DIR}/sequence.cpp
	${AOSDESIGNER_CORE_DIR}/editionsession.cpp
	${AOSDESIGNER_CORE_DIR}/editionsessionId.cpp
	${AOSDESIGNER_CORE_DIR}/library.cpp
)

# Resources system source files
set( AOSDESIGNER_CORE_RESOURCES_SOURCES
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resource.cpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourceprovider.cpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/resourcefactory.cpp
)

#------------------------------------------------------



#####################################################
# Resource files.

set( AOSDESIGNER_VIEW_RC
	${AOSDESIGNER_RC_DIR}/AOSDesigner.qrc
)

# RC files need to be processed by Qt wrapper to generate RC headers.
qt5_add_resources( AOSDESIGNER_VIEW_RESOURCES ${AOSDESIGNER_VIEW_RC} )

# RC files are isolated in a separate virtual directory.
source_group( designer\\view\\rc FILES ${AOSDESIGNER_VIEW_RC} )

# Group generated files in the same isolated virtual directory.
source_group( designer\\view\\generated\\rc FILES ${AOSDESIGNER_VIEW_RESOURCES} )

#####################################################
# UI files

set( AOSDESIGNER_VIEW_UI
	${AOSDESIGNER_UI_DIR}/mainwindow.ui
	${AOSDESIGNER_UI_DIR}/welcomescreen.ui
	${AOSDESIGNER_UI_DIR}/newprojectdialog.ui
	${AOSDESIGNER_UI_DIR}/newsequencedialog.ui
	${AOSDESIGNER_UI_DIR}/neweditionsessiondialog.ui
)

# UI files need to be processed by Qt wrapper to generate UI headers.
qt5_wrap_ui( AOSDESIGNER_VIEW_HEADERS_UI ${AOSDESIGNER_VIEW_UI} )

# Group all ui files in the same virtual directory.
source_group( designer\\view\\ui FILES ${AOSDESIGNER_VIEW_UI} )
# Group generated files in the same isolated virtual directory.
source_group( designer\\view\\generated\\ui FILES ${AOSDESIGNER_VIEW_HEADERS_UI} )

###################################################

# Additional groups
source_group( designer\\view FILES ${AOSDESIGNER_VIEW_HEADERS} ${AOSDESIGNER_VIEW_SOURCES} )
source_group( designer\\view\\dialog FILES ${AOSDESIGNER_DIALOG_HEADERS} ${AOSDESIGNER_DIALOG_SOURCES} )
source_group( designer\\view\\model FILES ${AOSDESIGNER_VIEW_MODEL_HEADERS} ${AOSDESIGNER_VIEW_MODEL_SOURCES} )
source_group( designer\\view\\editor FILES ${AOSDESIGNER_VIEW_EDITOR_HEADERS} ${AOSDESIGNER_VIEW_EDITOR_SOURCES} )
source_group( designer\\view\\editor\\canvas FILES ${AOSDESIGNER_VIEW_EDITOR_CANVAS_HEADERS} ${AOSDESIGNER_VIEW_EDITOR_CANVAS_SOURCES} )
source_group( designer\\view\\editor\\story FILES ${AOSDESIGNER_VIEW_EDITOR_STORY_HEADERS} ${AOSDESIGNER_VIEW_EDITOR_STORY_SOURCES} )
source_group( designer\\core FILES ${AOSDESIGNER_CORE_HEADERS} ${AOSDESIGNER_CORE_SOURCES} )
source_group( designer\\core\\resources FILES ${AOSDESIGNER_CORE_RESOURCES_HEADERS} ${AOSDESIGNER_CORE_RESOURCES_SOURCES} )
source_group( designer FILES ${AOSDESIGNER_APPLICATION_HEADERS} ${AOSDESIGNER_APPLICATION_SOURCES} )

####################################################
# Bind them all together.

# All the compiled sources.
set( AOSDESIGNER_ALL_SOURCES
	${AOSDESIGNER_CORE_SOURCES}
	${AOSDESIGNER_CORE_RESOURCES_SOURCES}
	${AOSDESIGNER_APPLICATION_SOURCES}
	${AOSDESIGNER_VIEW_SOURCES}
	${AOSDESIGNER_DIALOG_SOURCES}
	${AOSDESIGNER_VIEW_MODEL_SOURCES}
	${AOSDESIGNER_VIEW_EDITOR_SOURCES}
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_SOURCES}
	${AOSDESIGNER_VIEW_EDITOR_STORY_SOURCES}
	${AOSDESIGNER_VIEW_HEADERS_UI}
	${AOSDESIGNER_VIEW_RESOURCES}
)

# All the files of the project.
set( AOSDESIGNER_ALL_FILES ${AOSDESIGNER_ALL_SOURCES} ${AOSDESIGNER_ALL_HEADERS} )

include_directories( 
	${AOSDESIGNER_ROOT_DIR} 
	${CMAKE_CURRENT_BINARY_DIR} 
	${AOSLCPP_INCLUDE_DIRS}
	${UTILCPP_INCLUDE_DIR}
)

add_executable( aosdesigner ${AOSDESIGNER_ALL_FILES} )
target_link_libraries( aosdesigner
	${Boost_LIBRARIES}
	utilcpp 
	aoslcpp
)

qt5_use_modules( aosdesigner Widgets )

# We need the AOSL definition file in the build directory
add_custom_command( TARGET aosdesigner POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy ${AOSL_XSD_FILE} ${AOSDESIGNER_BUILD_DIR}
) 

add_custom_command( TARGET aosdesigner POST_BUILD 
	COMMAND python ${AOSDESIGNER_ROOT_DIR}/script/post_build.py 
		${AOSDESIGNER_BUILD_MODE} 
		${AOSDESIGNER_BUILD_DIR} 
)

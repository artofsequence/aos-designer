cmake_minimum_required( VERSION 2.8 )

project( AOS_Designer )

####################################################
# Dependencies.

# Boost
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
	${AOSDESIGNER_CORE_DIR}/Context.hpp
	${AOSDESIGNER_CORE_DIR}/Project.hpp
	${AOSDESIGNER_CORE_DIR}/Sequence.hpp
	${AOSDESIGNER_CORE_DIR}/SequenceId.hpp
	${AOSDESIGNER_CORE_DIR}/ProjectInfos.hpp
	${AOSDESIGNER_CORE_DIR}/SequenceInfos.hpp
	${AOSDESIGNER_CORE_DIR}/EditionSession.hpp
	${AOSDESIGNER_CORE_DIR}/EditionSessionId.hpp
	${AOSDESIGNER_CORE_DIR}/Library.hpp
)

# Resources system header files.
set( AOSDESIGNER_CORE_RESOURCES_HEADERS
	${AOSDESIGNER_CORE_RESOURCES_DIR}/Resource.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourcePtr.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourceRef.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourceProvider.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourceFactory.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourceInfo.hpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/URI.hpp
)


#-----------------------------------------------------------------



# Views header files.
set( AOSDESIGNER_VIEW_HEADERS
	${AOSDESIGNER_VIEW_DIR}/ApplicationView.hpp
	${AOSDESIGNER_VIEW_DIR}/MainWindow.hpp
	${AOSDESIGNER_VIEW_DIR}/ProjectView.hpp
	${AOSDESIGNER_VIEW_DIR}/SequenceListView.hpp
	${AOSDESIGNER_VIEW_DIR}/LibrariesView.hpp
	${AOSDESIGNER_VIEW_DIR}/ChangesView.hpp
	${AOSDESIGNER_VIEW_DIR}/ObjectsView.hpp
	${AOSDESIGNER_VIEW_DIR}/LayersView.hpp
	${AOSDESIGNER_VIEW_DIR}/ToolboxView.hpp
	${AOSDESIGNER_VIEW_DIR}/LogView.hpp
	${AOSDESIGNER_VIEW_DIR}/Dialogs.hpp
	${AOSDESIGNER_VIEW_DIR}/DesignerActions.hpp
	${AOSDESIGNER_VIEW_DIR}/EditionToolView.hpp
	${AOSDESIGNER_VIEW_DIR}/FreeWindow.hpp
	${AOSDESIGNER_VIEW_DIR}/FreeWindowManager.hpp
)   


# Dialog header files.
set( AOSDESIGNER_DIALOG_HEADERS
	${AOSDESIGNER_DIALOG_DIR}/WelcomeScreen.hpp
	${AOSDESIGNER_DIALOG_DIR}/NewProjectDialog.hpp
	${AOSDESIGNER_DIALOG_DIR}/NewSequenceDialog.hpp
	${AOSDESIGNER_DIALOG_DIR}/NewEditionSessionDialog.hpp
)

# View-model header files.
set( AOSDESIGNER_VIEW_MODEL_HEADERS
	${AOSDESIGNER_VIEW_MODEL_DIR}/CanvasObjectsModel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/CanvasLayersModel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/LayerObjectsModel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/LastChangesModel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/LibraryModel.hpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/ModelViewBinder.hpp
)


# Canvas editor views header files.
set( AOSDESIGNER_VIEW_EDITOR_CANVAS_HEADERS
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/CanvasView.hpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/CanvasGraphicsView.hpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/CanvasInvisibleObjectsView.hpp
)

# Story editor views header files.
set( AOSDESIGNER_VIEW_EDITOR_STORY_HEADERS
	${AOSDESIGNER_VIEW_EDITOR_STORY_DIR}/StoryView.hpp
)

# Editor views header files.
set( AOSDESIGNER_VIEW_EDITOR_HEADERS
	${AOSDESIGNER_VIEW_EDITOR_DIR}/EditorManager.hpp
	${AOSDESIGNER_VIEW_EDITOR_DIR}/Editor.hpp
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
	${AOSDESIGNER_ROOT_DIR}/Application.cpp
	${AOSDESIGNER_ROOT_DIR}/Paths.cpp
)


# Views source files.
set( AOSDESIGNER_VIEW_SOURCES 
	${AOSDESIGNER_VIEW_DIR}/ApplicationView.cpp
	${AOSDESIGNER_VIEW_DIR}/MainWindow.cpp
	${AOSDESIGNER_VIEW_DIR}/ProjectView.cpp
	${AOSDESIGNER_VIEW_DIR}/SequenceListView.cpp
	${AOSDESIGNER_VIEW_DIR}/LibrariesView.cpp
	${AOSDESIGNER_VIEW_DIR}/LogView.cpp
	${AOSDESIGNER_VIEW_DIR}/ObjectsView.cpp
	${AOSDESIGNER_VIEW_DIR}/LayersView.cpp
	${AOSDESIGNER_VIEW_DIR}/ToolboxView.cpp
	${AOSDESIGNER_VIEW_DIR}/ChangesView.cpp
	${AOSDESIGNER_VIEW_DIR}/Dialogs.cpp
	${AOSDESIGNER_VIEW_DIR}/DesignerActions.cpp
	${AOSDESIGNER_VIEW_DIR}/EditionToolView.cpp
	${AOSDESIGNER_VIEW_DIR}/FreeWindowManager.cpp
	${AOSDESIGNER_VIEW_DIR}/FreeWindow.cpp
)   


# Dialog source files.
set( AOSDESIGNER_DIALOG_SOURCES 
	${AOSDESIGNER_DIALOG_DIR}/WelcomeScreen.cpp
	${AOSDESIGNER_DIALOG_DIR}/NewProjectDialog.cpp
	${AOSDESIGNER_DIALOG_DIR}/NewSequenceDialog.cpp
	${AOSDESIGNER_DIALOG_DIR}/NewEditionSessionDialog.cpp
)


# View-model source files.
set( AOSDESIGNER_VIEW_MODEL_SOURCES 
	${AOSDESIGNER_VIEW_MODEL_DIR}/CanvasObjectsModel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/CanvasLayersModel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/LayerObjectsModel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/LastChangesModel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/LibraryModel.cpp
	${AOSDESIGNER_VIEW_MODEL_DIR}/ModelViewBinder.cpp
)

# Canvas editor views source files.
set( AOSDESIGNER_VIEW_EDITOR_CANVAS_SOURCES
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/CanvasView.cpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/CanvasGraphicsView.cpp
	${AOSDESIGNER_VIEW_EDITOR_CANVAS_DIR}/CanvasInvisibleObjectsView.cpp
)

# Story editor views source files.
set( AOSDESIGNER_VIEW_EDITOR_STORY_SOURCES
	${AOSDESIGNER_VIEW_EDITOR_STORY_DIR}/StoryView.cpp
)


# Editor views source files.
set( AOSDESIGNER_VIEW_EDITOR_SOURCES 
	${AOSDESIGNER_VIEW_EDITOR_DIR}/Editor.cpp
    ${AOSDESIGNER_VIEW_EDITOR_DIR}/EditorManager.cpp
)
	
#------------------------------------------------------

# Core source files
set( AOSDESIGNER_CORE_SOURCES
	${AOSDESIGNER_CORE_DIR}/Context.cpp
	${AOSDESIGNER_CORE_DIR}/Project.cpp
	${AOSDESIGNER_CORE_DIR}/Sequence.cpp
	${AOSDESIGNER_CORE_DIR}/EditionSession.cpp
	${AOSDESIGNER_CORE_DIR}/EditionSessionId.cpp
	${AOSDESIGNER_CORE_DIR}/Library.cpp
)

# Resources system source files
set( AOSDESIGNER_CORE_RESOURCES_SOURCES
	${AOSDESIGNER_CORE_RESOURCES_DIR}/Resource.cpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourceProvider.cpp
	${AOSDESIGNER_CORE_RESOURCES_DIR}/ResourceFactory.cpp
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
	${AOSDESIGNER_UI_DIR}/MainWindow.ui
	${AOSDESIGNER_UI_DIR}/WelcomeScreen.ui
	${AOSDESIGNER_UI_DIR}/NewProjectDialog.ui
	${AOSDESIGNER_UI_DIR}/NewSequenceDialog.ui
	${AOSDESIGNER_UI_DIR}/NewEditionSessionDialog.ui
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

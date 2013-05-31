cmake_minimum_required( VERSION 2.8 )

project( aosdesigner-frontend-qt )

####################################################
# Dependencies.

UTILCPP_USE_BOOST(
	system
	filesystem
)


set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
find_package( Qt5Widgets REQUIRED )

#####################################################
# Sub-directories.

set( AOSD_FRONTENDQT_DIR ${CMAKE_CURRENT_SOURCE_DIR} )

set( AOSD_FRONTENDQT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include )
set( AOSD_FRONTENDQT_INCLUDE_DIR ${AOSD_FRONTENDQT_INCLUDE_DIR} PARENT_SCOPE )

set( AOSD_FRONTENDQT_SOURCE_DIR ${AOSD_FRONTENDQT_DIR}/source )

set( AOSD_FRONTENDQT_RC_DIR ${AOSD_FRONTENDQT_DIR}/rc )
set( AOSD_FRONTENDQT_UI_DIR ${AOSD_FRONTENDQT_DIR}/ui )

set( AOSD_FRONTENDQT_DIALOG_DIR ${AOSD_FRONTENDQT_SOURCE_DIR}/dialog )
set( AOSD_FRONTENDQT_EDITOR_DIR ${AOSD_FRONTENDQT_SOURCE_DIR}/editor )
set( AOSD_FRONTENDQT_EDITOR_CANVAS_DIR ${AOSD_FRONTENDQT_EDITOR_DIR}/canvas )
set( AOSD_FRONTENDQT_EDITOR_STORY_DIR ${AOSD_FRONTENDQT_EDITOR_DIR}/story )
set( AOSD_FRONTENDQT_MODEL_DIR ${AOSD_FRONTENDQT_SOURCE_DIR}/model )

#####################################################
# Header files.

set( AOSD_FRONTENDQT_ROOT_HEADERS
	${AOSD_FRONTENDQT_SOURCE_DIR}/applicationview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/mainwindow.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/projectview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/sequencelistView.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/librariesview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/changesview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/objectsview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/layersview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/toolboxview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/logview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/dialogs.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/designeractions.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/editiontoolview.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/freewindow.hpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/freewindowmanager.hpp
)   


# Dialog header files.
set( AOSD_FRONTENDQT_DIALOG_HEADERS
	${AOSD_FRONTENDQT_DIALOG_DIR}/welcomescreen.hpp
	${AOSD_FRONTENDQT_DIALOG_DIR}/newprojectdialog.hpp
	${AOSD_FRONTENDQT_DIALOG_DIR}/newsequencedialog.hpp
	${AOSD_FRONTENDQT_DIALOG_DIR}/neweditionsessiondialog.hpp
)

# View-model header files.
set( AOSD_FRONTENDQT_MODEL_HEADERS
	${AOSD_FRONTENDQT_MODEL_DIR}/canvasobjectsmodel.hpp
	${AOSD_FRONTENDQT_MODEL_DIR}/canvaslayersmodel.hpp
	${AOSD_FRONTENDQT_MODEL_DIR}/layerobjectsmodel.hpp
	${AOSD_FRONTENDQT_MODEL_DIR}/lastchangesmodel.hpp
	${AOSD_FRONTENDQT_MODEL_DIR}/librarymodel.hpp
	${AOSD_FRONTENDQT_MODEL_DIR}/modelviewbinder.hpp
)


# Canvas editor views header files.
set( AOSD_FRONTENDQT_EDITOR_CANVAS_HEADERS
	${AOSD_FRONTENDQT_EDITOR_CANVAS_DIR}/canvasview.hpp
	${AOSD_FRONTENDQT_EDITOR_CANVAS_DIR}/canvasgraphicsview.hpp
	${AOSD_FRONTENDQT_EDITOR_CANVAS_DIR}/canvasinvisibleobjectsview.hpp
)

# Story editor views header files.
set( AOSD_FRONTENDQT_EDITOR_STORY_HEADERS
	${AOSD_FRONTENDQT_EDITOR_STORY_DIR}/storyview.hpp
)

# Editor views header files.
set( AOSD_FRONTENDQT_EDITOR_HEADERS
	${AOSD_FRONTENDQT_EDITOR_DIR}/editormanager.hpp
	${AOSD_FRONTENDQT_EDITOR_DIR}/editor.hpp
)

#-----------------------------------------------------------------

# All header files.
set( AOSD_FRONTENDQT_ALL_HEADERS
	${AOSD_FRONTENDQT_ROOT_HEADERS}
	${AOSD_FRONTENDQT_DIALOG_HEADERS}
	${AOSD_FRONTENDQT_MODEL_HEADERS}
	${AOSD_FRONTENDQT_EDITOR_HEADERS}
	${AOSD_FRONTENDQT_EDITOR_CANVAS_HEADERS}
	${AOSD_FRONTENDQT_EDITOR_STORY_HEADERS}
)

# Headers that depends on QObject
set( AOSD_FRONTENDQT_QOBJECT_HEADERS
	${AOSD_FRONTENDQT_ALL_HEADERS}
)
 

# Header files needs to be processed by Qt's pre-processor to generate Moc files.
qt5_wrap_cpp( AOSD_FRONTENDQT_QOBJECT_HEADERS_MOC ${AOSD_FRONTENDQT_QOBJECT_HEADERS} )

# Group generated files in the same isolated virtual directory.
source_group( "\\_generated\\moc" FILES ${AOSD_FRONTENDQT_QOBJECT_HEADERS_MOC} )


#####################################################
# Source files.

# Views source files.
set( AOSD_FRONTENDQT_ROOT_SOURCES 
	${AOSD_FRONTENDQT_SOURCE_DIR}/applicationview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/mainWindow.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/projectview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/sequencelistview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/librariesview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/logview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/objectsview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/layersview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/toolboxview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/changesview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/dialogs.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/designeractions.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/editiontoolview.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/freewindowmanager.cpp
	${AOSD_FRONTENDQT_SOURCE_DIR}/freewindow.cpp
)   


# Dialog source files.
set( AOSDESIGNER_DIALOG_SOURCES 
	${AOSD_FRONTENDQT_DIALOG_DIR}/welcomescreen.cpp
	${AOSD_FRONTENDQT_DIALOG_DIR}/newprojectdialog.cpp
	${AOSD_FRONTENDQT_DIALOG_DIR}/newsequencedialog.cpp
	${AOSD_FRONTENDQT_DIALOG_DIR}/neweditionsessiondialog.cpp
)


# View-model source files.
set( AOSD_FRONTENDQT_MODEL_SOURCES 
	${AOSD_FRONTENDQT_MODEL_DIR}/canvasobjectsmodel.cpp
	${AOSD_FRONTENDQT_MODEL_DIR}/canvaslayersmodel.cpp
	${AOSD_FRONTENDQT_MODEL_DIR}/layerobjectsmodel.cpp
	${AOSD_FRONTENDQT_MODEL_DIR}/lastchangesmodel.cpp
	${AOSD_FRONTENDQT_MODEL_DIR}/librarymodel.cpp
	${AOSD_FRONTENDQT_MODEL_DIR}/modelviewbinder.cpp
)

# Canvas editor views source files.
set( AOSD_FRONTENDQT_EDITOR_CANVAS_SOURCES
	${AOSD_FRONTENDQT_EDITOR_CANVAS_DIR}/canvasview.cpp
	${AOSD_FRONTENDQT_EDITOR_CANVAS_DIR}/canvasgraphicsView.cpp
	${AOSD_FRONTENDQT_EDITOR_CANVAS_DIR}/canvasinvisibleobjectsview.cpp
)

# Story editor views source files.
set( AOSD_FRONTENDQT_EDITOR_STORY_SOURCES
	${AOSD_FRONTENDQT_EDITOR_STORY_DIR}/storyview.cpp
)


# Editor views source files.
set( AOSD_FRONTENDQT_EDITOR_SOURCES 
	${AOSD_FRONTENDQT_EDITOR_DIR}/editor.cpp
	${AOSD_FRONTENDQT_EDITOR_DIR}/editormanager.cpp
)


#####################################################
# Resource files.

set( AOSD_FRONTENDQT_RC
	${AOSD_FRONTENDQT_RC_DIR}/AOSDesigner.qrc
)

# RC files need to be processed by Qt wrapper to generate RC headers.
qt5_add_resources( AOSD_FRONTENDQT_RESOURCES ${AOSD_FRONTENDQT_RC} )

# RC files are isolated in a separate virtual directory.
source_group( "\\frontendqt\\_rc" FILES ${AOSD_FRONTENDQT_RC} )

# Group generated files in the same isolated virtual directory.
source_group( "\\frontendqt\\_generated\\rc" FILES ${AOSD_FRONTENDQT_RESOURCES} )

#####################################################
# UI files

set( AOSD_FRONTENDQT_UI_FILES
	${AOSD_FRONTENDQT_UI_DIR}/mainwindow.ui
	${AOSD_FRONTENDQT_UI_DIR}/welcomescreen.ui
	${AOSD_FRONTENDQT_UI_DIR}/newprojectdialog.ui
	${AOSD_FRONTENDQT_UI_DIR}/newsequencedialog.ui
	${AOSD_FRONTENDQT_UI_DIR}/neweditionsessiondialog.ui
)

# UI files need to be processed by Qt wrapper to generate UI headers.
qt5_wrap_ui( AOSD_FRONTENDQT_GENERATED_HEADERS_UI ${AOSD_FRONTENDQT_UI_FILES} )

# Group all ui files in the same virtual directory.
source_group( "\\frontendqt\\_ui" FILES ${AOSD_FRONTENDQT_UI_FILES} )
# Group generated files in the same isolated virtual directory.
source_group( "\\frontendqt\\_generated\\ui" FILES ${AOSD_FRONTENDQT_GENERATED_HEADERS_UI} )

###################################################

# Additional groups
source_group( "\\frontendqt\\" FILES ${AOSD_FRONTENDQT_ROOT_HEADERS} ${AOSD_FRONTENDQT_ROOT_SOURCES} )
source_group( "\\frontendqt\\dialog" FILES ${AOSD_FRONTENDQT_DIALOG_HEADERS} ${AOSDESIGNER_DIALOG_SOURCES} )
source_group( "\\frontendqt\\model" FILES ${AOSD_FRONTENDQT_MODEL_HEADERS} ${AOSD_FRONTENDQT_MODEL_SOURCES} )
source_group( "\\frontendqt\\editor" FILES ${AOSD_FRONTENDQT_EDITOR_HEADERS} ${AOSD_FRONTENDQT_EDITOR_SOURCES} )
source_group( "\\frontendqt\\editor\\canvas" FILES ${AOSD_FRONTENDQT_EDITOR_CANVAS_HEADERS} ${AOSD_FRONTENDQT_EDITOR_CANVAS_SOURCES} )
source_group( "\\frontendqt\\editor\\story" FILES ${AOSD_FRONTENDQT_EDITOR_STORY_HEADERS} ${AOSD_FRONTENDQT_EDITOR_STORY_SOURCES} )

####################################################
# Bind them all together.

# All the compiled sources.
set( AOSD_FRONTENDQT_ALL_SOURCES
	${AOSD_FRONTENDQT_ROOT_SOURCES}
	${AOSD_FRONTENDQT_DIALOG_SOURCES}
	${AOSD_FRONTENDQT_MODEL_SOURCES}
	${AOSD_FRONTENDQT_EDITOR_SOURCES}
	${AOSD_FRONTENDQT_EDITOR_CANVAS_SOURCES}
	${AOSD_FRONTENDQT_EDITOR_STORY_SOURCES}
	${AOSD_FRONTENDQT_GENERATED_HEADERS_UI}
	${AOSD_FRONTENDQT_RESOURCES}
)

# All the files of the project.
set( AOSD_FRONTENDQT_ALL_FILES 
	${AOSD_FRONTENDQT_ALL_SOURCES} 
	${AOSD_FRONTENDQT_ALL_HEADERS}
)

UTILCPP_MAKE_LIBRARY( aosdesigner-frontend-qt SHARED
	SOURCES
		${AOSD_FRONTENDQT_ALL_FILES}
	INCLUDE_DIRS
		${AOSD_BACKEND_INCLUDE_DIR}
		${AOSD_FRONTENDQT_SOURCE_DIR}
		${AOSD_FRONTENDQT_INCLUDE_DIR}
		${AOSLCPP_INCLUDE_DIRS}
	LINK_TARGETS
		aosdesigner-backend
		aoslcpp
)

qt5_use_modules( aosdesigner-frontend-qt Widgets )

add_custom_command( TARGET aosdesigner-frontend-qt POST_BUILD 
	COMMAND python ${AOSDESIGNER_ROOT_DIR}/script/post_build.py 
		${AOSDESIGNER_BUILD_MODE} 
		${AOSDESIGNER_BUILD_DIR} 
)

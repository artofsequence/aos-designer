#ifndef HGUARD_AOSD_VIEW_MAINWINDOW_HPP__
#define HGUARD_AOSD_VIEW_MAINWINDOW_HPP__
#pragma once

#include <memory>
#include <map>
#include <QMainWindow>

#include "core/editionsessionid.hpp"
#include "view/designeractions.hpp"
#include "view/editor/editormanager.hpp"
#include "view/freewindowmanager.hpp"

class QMdiArea;

namespace Ui
{
	class MainWindow;
}

namespace aosd
{

namespace view
{
	 class ProjectView;
	 class ChangesView;
	 class ObjectsView;
	 class LibrariesView;
	 class LayersView;
	 class ToolboxView;
	 class LogView;

	/** Main window of the application.
		Hold all the views and visual tools but don't display them until getting in edition mode.
	**/
	class MainWindow
		: public QMainWindow
	{
		Q_OBJECT
	public:

		MainWindow();
		~MainWindow();

		/** Clear the windows currently open in the center of the window. */
		void clear_windows();
		
		/** Open edition mode : all edition views are open or available. **/
		void open_edition();

		/** Close edition mode : disable all editions views. */
		void close_edition();
		
		/** True if we are currently in edition mode, false otherwise. */
		bool is_edition_mode() const { return m_edition_mode; }

	private slots:

		/** Slot : called when a project have been opened. */
		void react_project_open( const backend::Project& project );

		/** Slot : called when a project have been closed. */
		void react_project_closed( const backend::Project& project );

	private:

		/** UI file defining the window look. */
		std::unique_ptr<Ui::MainWindow> m_ui;

		/** Tabs at the center of the window. */
		std::unique_ptr<QMdiArea> m_central_area;

		FreeWindowManager m_window_manager;
		EditorManager m_editor_manager;

		
		// Components of the edition interface:
		std::unique_ptr<ProjectView> m_project_view;
		std::unique_ptr<ChangesView> m_changes_view;
		std::unique_ptr<ObjectsView> m_objects_view;
		std::unique_ptr<LibrariesView> m_libraries_view;
		std::unique_ptr<LayersView> m_layers_view;
		std::unique_ptr<ToolboxView> m_toolbox_view;
		std::unique_ptr<LogView> m_log_view;

		// Manage and provide main actions (in the main menu for example)
		DesignerActions m_designer_actions;

		/// Are we in edition mode?
		bool m_edition_mode;
		
		/** Connect our slots to signals we want to react to. */
		void connect_signals();

		/** Create the menus from the actions. */
		void create_menus();

		/** Setup the views in their default configuration and positions. **/
		void setup_views_default();

		void closeEvent( QCloseEvent* closeEvent );
		
	};


}
}


#endif

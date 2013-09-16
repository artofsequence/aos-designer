#include "mainwindow.hpp"

#include <QMdiArea>
#include <QKeyEvent>

#include "ui_mainwindow.h"

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/editor.hpp>

#include "projectview.hpp"
#include "librariesview.hpp"
#include "changesview.hpp"
#include "objectsview.hpp"
#include "layersview.hpp"
#include "toolboxview.hpp"
#include "logview.hpp"
#include "editor/editor.hpp"
#include "designeractions.hpp"

namespace aosd
{
namespace view
{

	MainWindow::MainWindow()
		: QMainWindow( nullptr )
		, m_ui( new Ui::MainWindow )
		, m_central_area( new QMdiArea() )
		, m_window_manager( *m_central_area )
		, m_editor_manager( m_window_manager )
		, m_edition_mode( false )
		, m_project_view( new ProjectView() )
		, m_changes_view( new ChangesView() )
		, m_objects_view( new ObjectsView() )
		, m_libraries_view( new LibrariesView() )
		, m_layers_view( new LayersView() )
		, m_toolbox_view( new ToolboxView() )
		, m_log_view( new LogView() )
	{
		m_ui->setupUi( this );
		
		setWindowTitle( tr("Art Of Sequence") );
		setAttribute( Qt::WA_QuitOnClose, true );

		// basic infrastructure
		setCentralWidget( m_central_area.get() );

		// use default views setup 
		// TODO : add a way to get a saved view setup
		setup_views_default();
		create_menus();

		// don't allow edition without something to edit first!
		close_edition();

		connect_signals();

	}


	MainWindow::~MainWindow()
	{
		
	}


	void MainWindow::react_project_open( const backend::Project& project )
	{
		setWindowTitle( tr("%1 - Art Of Sequence").arg( QString::fromStdString( project.name() ), 0 ) );

	}


	void MainWindow::react_project_closed( const backend::Project& project )
	{
		setWindowTitle( tr("Art Of Sequence") );

	}


	void MainWindow::setup_views_default()
	{
		// Tabs should be on the top of windows, not at the bottom
		setTabPosition( Qt::LeftDockWidgetArea, QTabWidget::North );
		setTabPosition( Qt::RightDockWidgetArea, QTabWidget::North );
		setTabPosition( Qt::BottomDockWidgetArea, QTabWidget::North );
		setTabPosition( Qt::TopDockWidgetArea, QTabWidget::North );

		addDockWidget( Qt::LeftDockWidgetArea, m_project_view.get() );
		tabifyDockWidget( m_project_view.get(), m_changes_view.get() );
		tabifyDockWidget( m_project_view.get(), m_objects_view.get() );

		addDockWidget( Qt::RightDockWidgetArea, m_libraries_view.get() );
		tabifyDockWidget( m_libraries_view.get(), m_layers_view.get() );
		tabifyDockWidget( m_libraries_view.get(), m_toolbox_view.get() );

		addDockWidget( Qt::BottomDockWidgetArea, m_log_view.get() );

	}

	void MainWindow::connect_signals()
	{
		auto& context = backend::Context::instance();

		connect( &context, SIGNAL(project_open(const backend::Project&)), this, SLOT(react_project_open(const backend::Project&)) );
		connect( &context, SIGNAL(project_closed(const backend::Project&)), this, SLOT(react_project_closed(const backend::Project&)) );

	}

	void MainWindow::open_edition()
	{
		/*m_project_view->setVisible(true);
		m_changes_view->setVisible(true);
		m_objects_view->setVisible(true);
		m_libraries_view->setVisible(true);
		m_layers_view->setVisible(true);
		m_toolbox_view->setVisible(true);
		*/
		m_project_view->setEnabled(true);
		m_changes_view->setEnabled(true);
		m_objects_view->setEnabled(true);
		m_libraries_view->setEnabled(true);
		m_layers_view->setEnabled(true);
		m_toolbox_view->setEnabled(true);

		m_edition_mode = true;
	}

	void MainWindow::close_edition()
	{
		m_edition_mode = false;

		clear_windows();
		/*
		m_project_view->setVisible(false);
		m_changes_view->setVisible(false);
		m_objects_view->setVisible(false);
		m_libraries_view->setVisible(false);
		m_layers_view->setVisible(false);
		m_toolbox_view->setVisible(false);
		*/
		m_project_view->setEnabled(false);
		m_changes_view->setEnabled(false);
		m_objects_view->setEnabled(false);
		m_libraries_view->setEnabled(false);
		m_layers_view->setEnabled(false);
		m_toolbox_view->setEnabled(false);

	}


	void MainWindow::clear_windows()
	{
		m_editor_manager.clear();
		m_window_manager.clear();

	}

	void MainWindow::create_menus()
	{
		m_designer_actions.setup_menubar( *menuBar() );

	}

	void MainWindow::closeEvent( QCloseEvent* closeEvent )
	{
		// TODO : here ask the user about closing the project without saving
		closeEvent->accept();
		QMainWindow::closeEvent( closeEvent );
	}


}
}
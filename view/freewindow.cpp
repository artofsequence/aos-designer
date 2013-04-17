#include "freewindow.hpp"

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QToolBar>
#include <QSplitter>
#include <QAction>
#include <QMenu>


#include "utilcpp/assert.hpp"

namespace aosd
{
namespace view
{

	FreeWindow::FreeWindow( QWidget& widget, QMdiArea& window_area )
		: m_widget( widget )
		, m_window_area( window_area )
		, m_window( new QMdiSubWindow )
		, m_toolbar( new QToolBar )
		, m_splitter( new QSplitter )
		, m_dock_action( new QAction( tr("Dock Window"), nullptr ) )
		, m_float_action( new QAction( tr("Float Window"), nullptr ) )
		, m_is_inside( false )
	{
		m_splitter->setOrientation( Qt::Vertical );
		m_splitter->addWidget( m_toolbar.get() );
		m_splitter->addWidget( &m_widget );
		
		m_window->setWidget( m_splitter.get() );
		m_window->setWindowTitle( m_widget.windowTitle() );

		go_inside();
	}

	FreeWindow::~FreeWindow()
	{
		if( m_is_inside )
			terminate_inside_window();
		else
			terminate_outside_window();

		m_window->setWidget( nullptr );
		m_toolbar->setParent( nullptr );
		m_widget.setParent( nullptr );
	}

	void FreeWindow::initialize_inside_window()
	{
		m_toolbar->addAction( m_float_action.get() );
		connect( m_float_action.get(), SIGNAL( triggered() ), this, SLOT( react_get_outside() ) );
		m_window_area.addSubWindow( m_window.get() );
		m_window->show();
		
	}

	void FreeWindow::initialize_outside_window()
	{
		m_toolbar->addAction( m_dock_action.get() );
		connect( m_dock_action.get(), SIGNAL( triggered() ), this, SLOT( react_get_inside() ) );
		m_window->show();
	}

	void FreeWindow::terminate_inside_window()
	{
		m_window->hide();
		m_toolbar->removeAction( m_float_action.get() );
		m_window_area.removeSubWindow( m_window.get() );
	}


	void FreeWindow::terminate_outside_window()
	{
		m_window->hide();
		m_toolbar->removeAction( m_dock_action.get() );
	}



	void FreeWindow::go_inside()
	{
		terminate_outside_window();
		initialize_inside_window();
	}

	void FreeWindow::go_outside()
	{
		terminate_inside_window();
		initialize_outside_window();

	}

	void FreeWindow::react_get_inside()
	{
		go_inside();
	}

	void FreeWindow::react_get_outside()
	{
		go_outside();
	}





}
}
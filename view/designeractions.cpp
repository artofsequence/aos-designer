#include "view/designeractions.hpp"

#include <QString>
#include <QMenuBar>
#include "view/applicationview.hpp"
#include "core/context.hpp"

namespace aosd
{
namespace view
{
	// TODO : find a better way to manage all this...
	DesignerActions::DesignerActions()
		: m_quit( "&Quit", nullptr )
		, m_new_project( "&New Project", nullptr )
		, m_open_project( "&Open Project", nullptr )
		, m_close_project( "&Close Project", nullptr )
		, m_new_sequence( "&New Sequence", nullptr )
		, m_new_edition( "&New Edition Session", nullptr )
		, m_save_project( "&Save all", nullptr )
		, m_restore_project( "&Restore", nullptr )
	{
		{
			auto quit_tip = QObject::tr("Quit AOS Designer");
			m_quit.setStatusTip( quit_tip );
			m_quit.setToolTip( quit_tip );
			m_quit.setShortcut( QObject::tr("Ctrl+Q") );
			QObject::connect( &m_quit, SIGNAL(triggered()), ApplicationView::instance(), SLOT(quit()) );
		}

		auto* context = &core::Context::instance();

		{
			auto new_project_tip = QObject::tr("Create a new project. If a project is already open, it will be closed first.");
			m_new_project.setStatusTip( new_project_tip );
			m_new_project.setToolTip( new_project_tip );
			QObject::connect( &m_new_project, SIGNAL(triggered()), context, SLOT(new_project()) );
		}

		{
			auto open_project_tip = QObject::tr( "Open a project. If a project is already open, it will be closed first." );
			m_open_project.setStatusTip( open_project_tip );
			m_open_project.setToolTip( open_project_tip );
			QObject::connect( &m_open_project, SIGNAL(triggered()), context, SLOT(open_project()) );
		}

		{
			auto close_project_tip = QObject::tr( "Close the currently open project." );
			m_close_project.setStatusTip( close_project_tip );
			m_close_project.setToolTip( close_project_tip );
			QObject::connect( &m_close_project, SIGNAL(triggered()), context, SLOT(close_project()) );
		}

		{
			auto new_sequence_tip = QObject::tr( "Create a new sequence in the current project." );
			m_new_sequence.setStatusTip( new_sequence_tip );
			m_new_sequence.setToolTip( new_sequence_tip );
			QObject::connect( &m_new_sequence, SIGNAL(triggered()), context, SLOT(new_sequence()) );
		}

		{
			auto save_project_tip = QObject::tr( "Save the project and all the sequences and story-paths it contains." );
			m_save_project.setStatusTip( save_project_tip );
			m_save_project.setToolTip( save_project_tip );
			QObject::connect( &m_save_project, SIGNAL(triggered()), context, SLOT(save_project()) );
		}

		{
			auto restore_project_tip = QObject::tr( "Reload the last saved version of the project." );
			m_restore_project.setStatusTip( restore_project_tip );
			m_restore_project.setToolTip( restore_project_tip );
			QObject::connect( &m_restore_project, SIGNAL(triggered()), context, SLOT(restore_project()) );
		}


		{
			auto new_edition_tip = QObject::tr( "Create a new editable view of a path through the sequence." );
			m_new_edition.setStatusTip( new_edition_tip );
			m_new_edition.setToolTip( new_edition_tip );
			QObject::connect( &m_new_edition, SIGNAL(triggered()), context, SLOT(new_edition()) );
		}

	}

	void DesignerActions::setup_menubar( QMenuBar& menubar )
	{
		// Designer menu
		{
			auto menu_designer = menubar.addMenu( QObject::tr("&Designer") );

			menu_designer->addAction( &m_new_project );
			menu_designer->addAction( &m_open_project );
			menu_designer->addAction( &m_close_project );
			menu_designer->addSeparator();
			menu_designer->addAction( &m_quit );

		}

		// Project menu
		{
			auto menu_project = menubar.addMenu( QObject::tr("&Project") );

			menu_project->addAction( &m_save_project );
			menu_project->addAction( &m_restore_project );
			menu_project->addSeparator();
			menu_project->addAction( &m_new_sequence );
			
		}

		// Sequence menu
		{
			auto menu_sequence = menubar.addMenu( QObject::tr("&Sequence") );

			menu_sequence->addAction( &m_new_edition );
			menu_sequence->addSeparator();


		}

	}

}
}
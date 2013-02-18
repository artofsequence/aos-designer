#include "view/ProjectView.hpp"

#include <QTabWidget>

#include "view/SequenceListView.hpp"
#include "core/Context.hpp"
#include "core/Project.hpp"

namespace aosd
{
namespace view
{

	ProjectView::ProjectView()
		: QDockWidget( tr("Project") )
		, m_tabs( new QTabWidget() )
	{
		setVisible( false );

		setWidget( m_tabs.get() );

		m_tabs->addTab( new SequenceListView(), tr("Sequences") );

		auto& context = core::Context::instance();

		connect( &context, SIGNAL(project_open( const core::Project& )),		this, SLOT( react_project_open(const core::Project&) ) );
		connect( &context, SIGNAL(project_closed( const core::Project& )),		this, SLOT( react_project_closed(const core::Project&) ) );

	}

	ProjectView::~ProjectView()
	{

	}

	void ProjectView::react_project_open( const core::Project& project )
	{
		setWindowTitle( "Project : " + QString::fromStdString( project.name() ) );
		setVisible( true );
		setEnabled( true );
	}

	void ProjectView::react_project_closed( const core::Project& )
	{
		setWindowTitle( tr("Project") );
		setVisible( false );
		setEnabled( false );
	}

}
}
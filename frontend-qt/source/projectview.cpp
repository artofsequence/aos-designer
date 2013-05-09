#include "view/projectview.hpp"

#include <QTabWidget>

#include "view/sequencelistview.hpp"
#include "core/context.hpp"
#include "core/project.hpp"

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

		auto& context = backend::Context::instance();

		connect( &context, SIGNAL(project_open( const backend::Project& )),		this, SLOT( react_project_open(const backend::Project&) ) );
		connect( &context, SIGNAL(project_closed( const backend::Project& )),		this, SLOT( react_project_closed(const backend::Project&) ) );

	}

	ProjectView::~ProjectView()
	{

	}

	void ProjectView::react_project_open( const backend::Project& project )
	{
		setWindowTitle( "Project : " + QString::fromStdString( project.name() ) );
		setVisible( true );
		setEnabled( true );
	}

	void ProjectView::react_project_closed( const backend::Project& )
	{
		setWindowTitle( tr("Project") );
		setVisible( false );
		setEnabled( false );
	}

}
}
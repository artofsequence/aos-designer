#include "EditionToolView.hpp"

#include "core/Context.hpp"
#include "core/Project.hpp"
#include "core/EditionSession.hpp"

namespace aosd
{
namespace view
{


	EditionToolView::EditionToolView()
	{
		setAttribute( Qt::WA_ShowWithoutActivating ); // THINK : should it be child class relative?
		deactivate();

		const auto& context = core::Context::instance();

		connect( &context, SIGNAL( project_open( const core::Project& ) ), this, SLOT( react_project_open( const core::Project& ) ) );
		connect( &context, SIGNAL( project_closed( const core::Project& ) ), this, SLOT( react_project_closed( const core::Project& ) ) );

		if( context.is_project_open() )
			react_project_open( context.current_project() );
	}

	EditionToolView::~EditionToolView()
	{

	}

	void EditionToolView::react_project_open( const core::Project& project )
	{
		connect( &project, SIGNAL( edition_begin() ), this, SLOT( react_edition_begin() ) );
		connect( &project, SIGNAL( edition_end() ), this, SLOT( react_edition_end() ) );

		connect( &project, SIGNAL( edition_session_begin( const core::EditionSession& ) ), this, SLOT( react_edition_session_begin( const core::EditionSession& ) ) );
		connect( &project, SIGNAL( edition_session_end( const core::EditionSession& ) ), this, SLOT( react_edition_session_end( const core::EditionSession& ) ) );

		connect( &project, SIGNAL( edition_selected( const core::EditionSession& ) ), this, SLOT( react_edition_selected( const core::EditionSession& ) ) );
		connect( &project, SIGNAL( edition_deselected( const core::EditionSession& ) ), this, SLOT( react_edition_deselected( const core::EditionSession& ) ) );
		
		const auto* selected_session = project.selected_edition_session();
		if( selected_session )
		{
			react_edition_selected( *selected_session );
			react_edition_begin();
		}

		connect_project( project );

	}

	void EditionToolView::react_project_closed( const core::Project& project )
	{
		disconnect_project( project );
		disconnect( &project, 0, this, 0 );
	}

	void EditionToolView::react_edition_begin()
	{
		activate();
	}

	void EditionToolView::react_edition_end()
	{
		deactivate();
	}
	
	void EditionToolView::react_edition_session_begin( const core::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Beginning invalid edition session!" );
		begin_edition_session( edition_session );
	}

	void EditionToolView::react_edition_session_end( const core::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Ending invalid edition session!" );
		end_edition_session( edition_session );
	}

	void EditionToolView::react_edition_selected( const core::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Selected invalid edition session!" );
		connect_edition( edition_session );
	}

	void EditionToolView::react_edition_deselected( const core::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Deselected invalid edition session!" );
		disconnect_edition( edition_session );
	}

	void EditionToolView::change_state( bool is_active )
	{
		setVisible( is_active );
		setEnabled( is_active );
			
	}


	
}
}
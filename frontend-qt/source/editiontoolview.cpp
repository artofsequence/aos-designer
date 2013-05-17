#include "editiontoolview.hpp"

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/editionsession.hpp>

#include <utilcpp/assert.hpp>

namespace aosd
{
namespace view
{


	EditionToolView::EditionToolView()
	{
		setAttribute( Qt::WA_ShowWithoutActivating ); // THINK : should it be child class relative?
		deactivate();

		const auto& context = backend::Context::instance();

		connect( &context, SIGNAL( project_open( const backend::Project& ) ), this, SLOT( react_project_open( const backend::Project& ) ) );
		connect( &context, SIGNAL( project_closed( const backend::Project& ) ), this, SLOT( react_project_closed( const backend::Project& ) ) );

		if( context.is_project_open() )
			react_project_open( context.current_project() );
	}

	EditionToolView::~EditionToolView()
	{

	}

	void EditionToolView::react_project_open( const backend::Project& project )
	{
		connect( &project, SIGNAL( edition_begin() ), this, SLOT( react_edition_begin() ) );
		connect( &project, SIGNAL( edition_end() ), this, SLOT( react_edition_end() ) );

		connect( &project, SIGNAL( edition_session_begin( const backend::EditionSession& ) ), this, SLOT( react_edition_session_begin( const backend::EditionSession& ) ) );
		connect( &project, SIGNAL( edition_session_end( const backend::EditionSession& ) ), this, SLOT( react_edition_session_end( const backend::EditionSession& ) ) );

		connect( &project, SIGNAL( edition_selected( const backend::EditionSession& ) ), this, SLOT( react_edition_selected( const backend::EditionSession& ) ) );
		connect( &project, SIGNAL( edition_deselected( const backend::EditionSession& ) ), this, SLOT( react_edition_deselected( const backend::EditionSession& ) ) );
		
		const auto* selected_session = project.selected_edition_session();
		if( selected_session )
		{
			react_edition_selected( *selected_session );
			react_edition_begin();
		}

		connect_project( project );

	}

	void EditionToolView::react_project_closed( const backend::Project& project )
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
	
	void EditionToolView::react_edition_session_begin( const backend::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Beginning invalid edition session!" );
		begin_edition_session( edition_session );
	}

	void EditionToolView::react_edition_session_end( const backend::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Ending invalid edition session!" );
		end_edition_session( edition_session );
	}

	void EditionToolView::react_edition_selected( const backend::EditionSession& edition_session )
	{
		UTILCPP_ASSERT( edition_session.is_valid(), "Selected invalid edition session!" );
		connect_edition( edition_session );
	}

	void EditionToolView::react_edition_deselected( const backend::EditionSession& edition_session )
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
#include "editiontoolview.hpp"

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/editor.hpp>

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

		connect( &project, SIGNAL( editor_begin( const backend::Editor& ) ), this, SLOT( react_editor_begin( const backend::Editor& ) ) );
		connect( &project, SIGNAL( editor_end( const backend::Editor& ) ), this, SLOT( react_editor_end( const backend::Editor& ) ) );

		connect( &project, SIGNAL( edition_selected( const backend::Editor& ) ), this, SLOT( react_edition_selected( const backend::Editor& ) ) );
		connect( &project, SIGNAL( edition_deselected( const backend::Editor& ) ), this, SLOT( react_edition_deselected( const backend::Editor& ) ) );
		
		const auto* selected_session = project.selected_editor();
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
	
	void EditionToolView::react_editor_begin( const backend::Editor& editor )
	{
		UTILCPP_ASSERT( editor.is_valid(), "Beginning invalid editor!" );
		begin_editor( editor );
	}

	void EditionToolView::react_editor_end( const backend::Editor& editor )
	{
		UTILCPP_ASSERT( editor.is_valid(), "Ending invalid editor!" );
		end_editor( editor );
	}

	void EditionToolView::react_edition_selected( const backend::Editor& editor )
	{
		UTILCPP_ASSERT( editor.is_valid(), "Selected invalid editor!" );
		connect_edition( editor );
	}

	void EditionToolView::react_edition_deselected( const backend::Editor& editor )
	{
		UTILCPP_ASSERT( editor.is_valid(), "Deselected invalid editor!" );
		disconnect_edition( editor );
	}

	void EditionToolView::change_state( bool is_active )
	{
		setVisible( is_active );
		setEnabled( is_active );
			
	}


	
}
}
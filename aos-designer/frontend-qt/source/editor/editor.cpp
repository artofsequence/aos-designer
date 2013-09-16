#include "editor.hpp"

#include <utilcpp/log.hpp>

#include <QCloseEvent>
#include <QPushButton>

#include "editor/canvas/canvasview.hpp"
#include "editor/story/storyview.hpp"
#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/editor.hpp>

namespace aosd
{
namespace view
{
	Editor::Editor( const  backend::Editor& editor )
		: m_canvas_view( new CanvasView )
		, m_story_view( new StoryView )
		, m_title( QString::fromStdString( editor.name() ) )
		, m_editor_id( editor.id() )
		, m_is_closing( false )
	{
		setOrientation( Qt::Vertical );

		addWidget( m_canvas_view.get() );
		addWidget( m_story_view.get() );

		setWindowTitle( m_title );
				
		UTILCPP_LOG << "Created Editor view for editor \"" << m_title.toStdString() << "\"";

		const auto& project = backend::Context::instance().current_project();
		auto sequence = project.find_sequence( editor.sequence_id() );
		update( editor.canvas(), sequence->library(), project.library() );

		setFocusPolicy( Qt::StrongFocus );
	}

	Editor::~Editor()
	{
		UTILCPP_LOG << "Destroyed Editor view for editor \"" << m_title.toStdString() << "\"";
	}

	
	void Editor::closeEvent( QCloseEvent* closeEvent )
	{
		UTILCPP_ASSERT_NOT_NULL( closeEvent );
		
		m_is_closing = true;

		// the user did close the window : delete the associated session id
		if( backend::Context::instance().delete_edition( m_editor_id ) )
		{
			QSplitter::closeEvent( closeEvent );
		}
		else
		{
			closeEvent->ignore();
		}

		m_is_closing = false;

	}


	void Editor::focusInEvent( QFocusEvent* event )
	{
		UTILCPP_ASSERT_NOT_NULL( event );
		
		auto selected_edittion_session = backend::Context::instance().selected_editor();
		if( selected_edittion_session
		&&	selected_edittion_session->id() != this->editor_id()
		)
		{
			backend::Context::instance().select_editor( this->editor_id() );
		}
		

		QSplitter::focusInEvent( event );
	}

	void Editor::update( const aosl::Canvas& canvas, const backend::Library& sequence_library, const backend::Library& project_library )
	{
		m_canvas_view->update( canvas, sequence_library, project_library );
	}



}

}
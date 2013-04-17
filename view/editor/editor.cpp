#include "editor.hpp"

#include "utilcpp/log.hpp"

#include <QCloseEvent>
#include <QPushButton>

#include "view/editor/canvas/canvasview.hpp"
#include "view/editor/story/storyview.hpp"
#include "core/context.hpp"
#include "core/project.hpp"
#include "core/sequence.hpp"
#include "core/editionsession.hpp"

namespace aosd
{
namespace view
{
	Editor::Editor( const  core::EditionSession& edition_session )
		: m_canvas_view( new CanvasView )
		, m_story_view( new StoryView )
		, m_title( QString::fromStdString( edition_session.name() ) )
		, m_session_id( edition_session.id() )
		, m_is_closing( false )
	{
		setOrientation( Qt::Vertical );

		addWidget( m_canvas_view.get() );
		addWidget( m_story_view.get() );

		setWindowTitle( m_title );
				
		UTILCPP_LOG << "Created Editor view for edition session \"" << m_title.toStdString() << "\"";

		const auto& project = core::Context::instance().current_project();
		auto sequence = project.find_sequence( edition_session.sequence_id() );
		update( edition_session.canvas(), sequence->library(), project.library() );

		setFocusPolicy( Qt::StrongFocus );
	}

	Editor::~Editor()
	{
		UTILCPP_LOG << "Destroyed Editor view for edition session \"" << m_title.toStdString() << "\"";
	}

	
	void Editor::closeEvent( QCloseEvent* closeEvent )
	{
		UTILCPP_ASSERT_NOT_NULL( closeEvent );
		
		m_is_closing = true;

		// the user did close the window : delete the associated session id
		if( core::Context::instance().delete_edition( m_session_id ) )
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
		
		auto selected_edittion_session = core::Context::instance().selected_edition_session();
		if( selected_edittion_session
		&&	selected_edittion_session->id() != this->session_id()
		)
		{
			core::Context::instance().select_edition_session( this->session_id() );
		}
		

		QSplitter::focusInEvent( event );
	}

	void Editor::update( const aosl::Canvas& canvas, const core::Library& sequence_library, const core::Library& project_library )
	{
		m_canvas_view->update( canvas, sequence_library, project_library );
	}



}

}
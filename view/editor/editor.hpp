#ifndef HGUARD_AOSD_EDITOR_HPP__
#define HGUARD_AOSD_EDITOR_HPP__
#pragma once

#include <memory>
#include <string>
#include <QSplitter>

#include "core/editionsessionid.hpp"

class QSplitter;
class QDockWidget;
class QMdiSubWindow;

namespace aosl
{
	class Canvas;
}

namespace aosd
{
namespace core
{ 
	class EditionSession; 
	class Library;
}

namespace view
{

	class CanvasView;
	class StoryView;

	/** Display the canvas and the story structure view for a specific path through the stages.
		Every information displayed is dependent on the path followed in the sequence.
	*/
	class Editor
		: public QSplitter
	{
		Q_OBJECT
	public:
		
		explicit Editor( const core::EditionSession& edition_session );
		~Editor();

		QString title() const { return m_title; }

		core::EditionSessionId session_id() const { return m_session_id; }

		bool is_closing() const { return m_is_closing; }

		void update( const aosl::Canvas& canvas, const core::Library& sequence_library, const core::Library& project_library );
		

	private slots:


	private:
		
		std::unique_ptr<CanvasView> m_canvas_view;
		std::unique_ptr<StoryView> m_story_view;
		
		QString m_title;
		core::EditionSessionId m_session_id;

		bool m_is_closing;
		
		/** We need to delete the edition session when closed. */
		void closeEvent( QCloseEvent* closeEvent );

		/** We need to detect when there is a change of focus to this editor. */
		void focusInEvent( QFocusEvent* event );
		
	};

}
}


#endif
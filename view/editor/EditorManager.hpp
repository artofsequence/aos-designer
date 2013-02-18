#ifndef HGUARD_AOSD_VIEW_EDITORMANAGER_HPP__
#define HGUARD_AOSD_VIEW_EDITORMANAGER_HPP__
#pragma once

#include <map>
#include <memory>
#include <QObject>

#include "core/EditionSessionId.hpp"


namespace aosd
{
namespace core
{
	class Project;
	class EditionSession;
	class Sequence;
}
namespace view
{
	class Editor;
	class FreeWindowManager;

	class EditorManager
		: public QObject
	{
		Q_OBJECT;
	public:
	
		explicit EditorManager( FreeWindowManager& window_manager );
		~EditorManager();
		
	public slots:
			
		/** Select visually the editor corresponding to the provided session id. */
		void select_editor( core::EditionSessionId session_id );

		/** Create and register an editor to be displayed to allow edition of the provided edition session. **/
		void add_editor( const core::EditionSession& edition_session );

		void remove_editor( const core::EditionSession& edition_session );
		void remove_editor( core::EditionSessionId session_id );

		/** Remove all editors from the display. */
		void clear();

	private slots:

		/** Slot : called when a project have been opened. */
		void react_project_open( const core::Project& project );

		/** Slot : called when a project have been closed. */
		void react_project_closed( const core::Project& project );

		/** Slot : called when a new sequence have been created. */
		void react_sequence_created( const core::Sequence& sequence );

		/** Slot : called when a sequence have been deleted. */
		void react_sequence_deleted( const core::Sequence& sequence );

		/** Slot : called when an edition session is beginning. */
		void react_edition_session_begin( const core::EditionSession& edition_session );

		/** Slot : called when an edition session is ending. */
		void react_edition_session_end( const core::EditionSession& edition_session );


	private:

		std::map< core::EditionSessionId, std::unique_ptr<Editor> > m_editor_registry;

		FreeWindowManager& m_window_manager;

		Editor* find_editor( core::EditionSessionId session_id );

	};


}
}


#endif

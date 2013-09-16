#ifndef HGUARD_AOSD_VIEW_EDITORMANAGER_HPP__
#define HGUARD_AOSD_VIEW_EDITORMANAGER_HPP__
#pragma once

#include <map>
#include <memory>
#include <QObject>

#include <aosdesigner/backend/id.hpp>


namespace aosd
{
namespace backend
{
	class Project;
	class Editor;
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
		void select_editor( backend::EditorId editor_id );

		/** Create and register an editor to be displayed to allow edition of the provided editor. **/
		void add_editor( const backend::Editor& editor );

		void remove_editor( const backend::Editor& editor );
		void remove_editor( backend::EditorId editor_id );

		/** Remove all editors from the display. */
		void clear();

	private slots:

		/** Slot : called when a project have been opened. */
		void react_project_open( const backend::Project& project );

		/** Slot : called when a project have been closed. */
		void react_project_closed( const backend::Project& project );

		/** Slot : called when a new sequence have been created. */
		void react_sequence_created( const backend::Sequence& sequence );

		/** Slot : called when a sequence have been deleted. */
		void react_sequence_deleted( const backend::Sequence& sequence );

		/** Slot : called when an editor is beginning. */
		void react_editor_begin( const backend::Editor& editor );

		/** Slot : called when an editor is ending. */
		void react_editor_end( const backend::Editor& editor );


	private:

		std::map< backend::EditorId, std::unique_ptr<Editor> > m_editor_registry;

		FreeWindowManager& m_window_manager;

		Editor* find_editor( backend::EditorId editor_id );

	};


}
}


#endif

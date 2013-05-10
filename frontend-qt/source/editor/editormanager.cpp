#include "editormanager.hpp"

#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/editionsession.hpp>

#include "editor.hpp"
#include "../freewindowmanager.hpp"

namespace aosd
{
namespace view
{

	EditorManager::EditorManager( FreeWindowManager& window_manager )
		: m_window_manager( window_manager )
	{
		auto& context = backend::Context::instance();

		connect( &context, SIGNAL(project_open(const backend::Project&)), this, SLOT(react_project_open(const backend::Project&)) );
		connect( &context, SIGNAL(project_closed(const backend::Project&)), this, SLOT(react_project_closed(const backend::Project&)) );

	}

	EditorManager::~EditorManager()
	{
		clear();
	}


	void EditorManager::clear()
	{
		for( auto editor_it = m_editor_registry.begin(); editor_it != m_editor_registry.end(); ++editor_it )
		{
			m_window_manager.remove_window( *editor_it->second );
		}

		m_editor_registry.clear();
	}

	void EditorManager::react_project_open( const backend::Project& project )
	{
		connect( &project, SIGNAL(edition_session_begin(const backend::EditionSession&)), this, SLOT(react_edition_session_begin(const backend::EditionSession&)) );
		connect( &project, SIGNAL(edition_session_end(const backend::EditionSession&)), this, SLOT(react_edition_session_end(const backend::EditionSession&)), Qt::QueuedConnection );

		connect( &project, SIGNAL(sequence_created(const backend::Sequence&)), this, SLOT(react_sequence_created(const backend::Sequence&)) );
		connect( &project, SIGNAL(sequence_deleted(const backend::Sequence&)), this, SLOT(react_sequence_deleted(const backend::Sequence&)), Qt::QueuedConnection );

		const auto* initial_session_selection = project.selected_edition_session();

		project.foreach_edition( [&]( const backend::EditionSession& edition_session ) 
		{
			add_editor( edition_session );
		});

		if( initial_session_selection )
		{
			backend::Context::instance().select_edition_session( initial_session_selection->id() );
			select_editor( initial_session_selection->id() );
		}

	}


	void EditorManager::react_project_closed( const backend::Project& project )
	{
		disconnect( &project, 0, this, 0 );

		clear();

	}


	void EditorManager::react_edition_session_begin( const backend::EditionSession& edition_session )
	{
		add_editor( edition_session );
	}

	void EditorManager::react_edition_session_end( const backend::EditionSession& edition_session )
	{
		remove_editor( edition_session );
	}


	void EditorManager::react_sequence_created( const backend::Sequence& sequence )
	{

	}

	void EditorManager::react_sequence_deleted( const backend::Sequence& sequence )
	{

	}


	void EditorManager::select_editor( backend::EditionSessionId session_id )
	{
		auto editor = find_editor( session_id );
		if( editor )
		{
			editor->setFocus();
		}
	}

	Editor* EditorManager::find_editor( backend::EditionSessionId session_id )
	{
		auto editor_it = m_editor_registry.find( session_id );
		if( editor_it != m_editor_registry.end() )
			return editor_it->second.get();
		else
			return nullptr;
		
	}

	void EditorManager::add_editor( const backend::EditionSession& edition_session )
	{
		auto editor = std::unique_ptr<Editor>( new Editor( edition_session ) );
		m_window_manager.add_window( *editor );

		m_editor_registry.insert( std::make_pair( edition_session.id(), std::move( editor ) ) );
	}

	void EditorManager::remove_editor( const backend::EditionSession& edition_session )
	{
		remove_editor( edition_session.id() );
	}

	void EditorManager::remove_editor( backend::EditionSessionId session_id )
	{
		// TODO : do it in one search instead of two
		auto editor = find_editor( session_id );
		if( editor )
		{
			m_window_manager.remove_window( *editor );
			m_editor_registry.erase( session_id );
		}
	}

}
}
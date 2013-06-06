#include "editormanager.hpp"

#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/editor.hpp>

#include "editor/editor.hpp"
#include "freewindowmanager.hpp"

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
		connect( &project, SIGNAL(editor_begin(const backend::Editor&)), this, SLOT(react_editor_begin(const backend::Editor&)) );
		connect( &project, SIGNAL(editor_end(const backend::Editor&)), this, SLOT(react_editor_end(const backend::Editor&)), Qt::QueuedConnection );

		connect( &project, SIGNAL(sequence_created(const backend::Sequence&)), this, SLOT(react_sequence_created(const backend::Sequence&)) );
		connect( &project, SIGNAL(sequence_deleted(const backend::Sequence&)), this, SLOT(react_sequence_deleted(const backend::Sequence&)), Qt::QueuedConnection );

		const auto* initial_editor_selection = project.selected_editor();

		project.foreach_edition( [&]( const backend::Editor& editor ) 
		{
			add_editor( editor );
		});

		if( initial_editor_selection )
		{
			backend::Context::instance().select_editor( initial_editor_selection->id() );
			select_editor( initial_editor_selection->id() );
		}

	}


	void EditorManager::react_project_closed( const backend::Project& project )
	{
		disconnect( &project, 0, this, 0 );

		clear();

	}


	void EditorManager::react_editor_begin( const backend::Editor& editor )
	{
		add_editor( editor );
	}

	void EditorManager::react_editor_end( const backend::Editor& editor )
	{
		remove_editor( editor );
	}


	void EditorManager::react_sequence_created( const backend::Sequence& sequence )
	{

	}

	void EditorManager::react_sequence_deleted( const backend::Sequence& sequence )
	{

	}


	void EditorManager::select_editor( backend::EditorId editor_id )
	{
		auto editor = find_editor( editor_id );
		if( editor )
		{
			editor->setFocus();
		}
	}

	Editor* EditorManager::find_editor( backend::EditorId editor_id )
	{
		auto editor_it = m_editor_registry.find( editor_id );
		if( editor_it != m_editor_registry.end() )
			return editor_it->second.get();
		else
			return nullptr;
		
	}

	void EditorManager::add_editor( const backend::Editor& editor )
	{
		auto editor = std::unique_ptr<Editor>( new Editor( editor ) );
		m_window_manager.add_window( *editor );

		m_editor_registry.insert( std::make_pair( editor.id(), std::move( editor ) ) );
	}

	void EditorManager::remove_editor( const backend::Editor& editor )
	{
		remove_editor( editor.id() );
	}

	void EditorManager::remove_editor( backend::EditorId editor_id )
	{
		// TODO : do it in one search instead of two
		auto editor = find_editor( editor_id );
		if( editor )
		{
			m_window_manager.remove_window( *editor );
			m_editor_registry.erase( editor_id );
		}
	}

}
}
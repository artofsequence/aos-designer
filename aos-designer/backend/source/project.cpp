#include <aosdesigner/backend/project.hpp>

#include <vector>
#include <boost/container/flat_map.hpp>
#include <boost/thread/synchronized_value.hpp>

#include <utilcpp/assert.hpp>
#include <utilcpp/make_unique.hpp>

#include <aosl/sequence.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/events/projectevents.hpp>
#include "workspaceinternalapi.hpp"

namespace aosd {
namespace backend {


	using boost::container::flat_map;

	class Project::Impl
	{
	public:
		explicit Impl( Project& project, ProjectInfo project_info );

		void add( std::shared_ptr<Editor> editor );
		void add( std::shared_ptr<Library> library );

		EditorId open_editor( EditorInfo info );

		ProjectInfo info() const { return *m_info; }

		std::shared_ptr<Sequence> find_or_load( const SequenceId& sequence_id );
		
		SequenceInfo find_info( const SequenceId& );

	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		Project& m_project;
		boost::synchronized_value<ProjectInfo> m_info;

		flat_map< LibraryId, std::shared_ptr<Library> >		m_loaded_libraries;
		flat_map< EditorId, std::shared_ptr<Editor> >		m_open_editors;
		flat_map< SequenceId, std::weak_ptr<Sequence> >		m_loaded_sequences;

	};

	Project::Impl::Impl( Project& project, ProjectInfo project_info )
		: m_project( project )
		, m_info( project_info )
	{
		for( const auto& editor_info : project_info.editor_list )
		{
			m_project.open_editor( editor_info ); // deffer to update
		}
	}

	EditorId Project::Impl::open_editor( EditorInfo info )
	{
		// TODO: add checks
		// check that the sequence is registered in this project
		
		auto sequence = find_or_load( info.sequence_id );
		if( !sequence )
			return EditorId(); // failed! TODO: maybe do something else?

		auto editor = std::make_shared<Editor>( m_project.workspace(), std::move(info), sequence );
		m_open_editors.insert( std::make_pair( editor->id(), editor ) );
		m_project.workspace().internal_api().add_to_registry( editor );

		event::EditorOpen ev;
		ev.editor_info = editor->info();
		m_project.publish( ev );

		return editor->id();
	}

	std::shared_ptr<Sequence> Project::Impl::find_or_load( const SequenceId& sequence_id )
	{
		auto find_it = m_loaded_sequences.find( sequence_id );
		if( find_it != end( m_loaded_sequences ) )
		{
			if( auto sequence = find_it->second.lock() )
			{
				return sequence; // ok found and it's alive
			}
			else
			{
				m_loaded_sequences.erase( find_it ); // not alive anymore, prevent next search.
			}
		}

		// The Sequence is not alive so we need to load it.
		// But first, find info and aosl data.
		auto info = find_info( sequence_id );
		aosl::Sequence aosl_sequence = m_project.workspace().internal_api().data_provider().get_aosl_sequence( info.aosl_location );
		
		auto sequence = std::make_shared<Sequence>( m_project.workspace(), info, aosl_sequence );

		return sequence;
	}

	SequenceInfo Project::Impl::find_info( const SequenceId& sequence_id )
	{
		const ProjectInfo project_info = *m_info;
		for( auto& sequence_info : project_info.sequence_list )
			if( sequence_info.id == sequence_id )
				return sequence_info;
		return SequenceInfo();
	}



	/////////////////////////////////////////////////////////


	Project::Project( Workspace& workspace, ProjectInfo info )
		: WorkspaceObject( workspace, info.id )
		, m_impl( std::make_unique<Impl>( *this, std::move(info) ) )
	{

	}

	Project::~Project()
	{

	}

	aosd::backend::ProjectInfo Project::info() const
	{
		return m_impl->info();
	}


	future<void> Project::add_sequence( SequenceInfo info )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<void> Project::remove_sequence( SequenceId sequence_id )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<void> Project::add_library( LibraryInfo info )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<void> Project::remove_library( LibraryId library_id )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<EditorId> Project::open_editor( EditorInfo info )
	{
		return schedule( [this,info]{ return m_impl->open_editor( info ); } );
	}

	future<void> Project::close_editor( EditorId editor_id )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

}}
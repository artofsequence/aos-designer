#include <aosdesigner/backend/project.hpp>

#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <utilcpp/assert.hpp>

#include <aosdesigner/backend/projectinfo.hpp>
#include <aosdesigner/backend/sequenceinfo.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/editorinfo.hpp>
#include <aosdesigner/backend/paths.hpp>

namespace aosd
{
namespace backend
{

	Project::Project( Context& context, const ProjectInfo& info )
		: m_context( context )
		, m_location( info.location )
		, m_name( info.name )
		, m_directory_path( info.location.parent_path() )
		, m_selected_session( nullptr )
		, m_library( m_context )
	{
		UTILCPP_ASSERT( is_valid(info), "Tried to construct a Project with invalid project info!" );
	}

	Project::Project( Context& context, const bfs::path& project_file_path )
		: m_context( context )
		, m_location( project_file_path )
		, m_directory_path( project_file_path.parent_path() )
		, m_selected_session( nullptr )
		, m_library( m_context )
	{
		UTILCPP_ASSERT( !project_file_path.empty(), "Tried to construct a Project at an empty path!" );
		UTILCPP_ASSERT( bfs::is_regular_file( m_location ), "Tried to create a project with an invalid file path! Path : " << m_location )
		UTILCPP_ASSERT( bfs::is_directory( m_directory_path ), "Wow, what's wrong with that project's directory? Path : " << m_directory_path )

		// THINK : make it  a throwing test?
		UTILCPP_ASSERT( boost::filesystem::exists( project_file_path ), "Tried to construct a Project with a path that don't exist!" ); 

		// THINK : move that in a separate function?
		using namespace boost::property_tree;
		ptree info;

		try
		{
			bfs::ifstream filestream( project_file_path );			
			read_xml( filestream, info );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project file loading : \n" << boost::diagnostic_information(e);
		}

		try
		{
			m_name = info.get<std::string>( "project.name" );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project's properties reading : \n" << boost::diagnostic_information(e);
		}

		try
		{
			auto sequences = info.get_child( "project.sequences", ptree() );

			if( !sequences.empty() )
			{
				for( const auto& sequence_info_it : sequences )
				{
					if( sequence_info_it.first == "sequence" )
					{
						const bfs::path sequence_location = sequence_info_it.second.get_value<std::string>();
						add_sequence( std::unique_ptr<Sequence>( new Sequence( *this, sequence_location ) ) );

						UTILCPP_LOG << "Loaded Sequence : " << m_sequences.back()->name() << " [" << m_sequences.back()->id() << "]";
					}
					else
					{
						UTILCPP_LOG_ERROR << "Found an unknown tag! Should be \"sequence\" instead of \"" << sequence_info_it.first << "\"";
					}

				}
			}
			else
			{
				UTILCPP_LOG << "No sequences in this project.";
			}
			
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project's sequences loading : \n" << boost::diagnostic_information(e);
		}

		try
		{
			auto editors = info.get_child( "project.edition", ptree() );

			if( !editors.empty() )
			{
				for( const auto& editor_it : editors )
				{
					if( editor_it.first == "session" )
					{
						EditorId editor_id;
						try
						{
							 editor_id = editor_it.second.get_value<EditorId>();
						}
						catch (const boost::exception& e)
						{
							UTILCPP_LOG_ERROR << "Failed to interpret editor id : [" << editor_it.second.get_value<std::string>() << "] : \n" << boost::diagnostic_information(e);
						}
						
						if( is_valid( editor_id ) )
						{
							try
							{
								const bfs::path editor_file_location = directory_path() / path::EDITION_SESSION_FILE( to_string(editor_id) );
								auto session = std::unique_ptr<Editor>( new Editor( *this, editor_file_location ) );
								if( session->is_valid() )
								{
									add_edition( std::move(session) );

									UTILCPP_LOG << "Loaded editor : [" << editor_id << "]";
								}
								
							}
							catch( const boost::exception& e )
							{
								UTILCPP_LOG_ERROR << "Failed to load editor [" << editor_id << "] : \n" << boost::diagnostic_information(e);
							}
						}
						else
						{
							UTILCPP_LOG_ERROR << "Invalid session id found - certainly due to some problem in a previous working session.";
						}
						
					}
					else if( editor_it.first != "selected" )
					{
						UTILCPP_LOG_ERROR << "Found an unknown tag! Should be \"session\" instead of \"" << editor_it.first << "\"";
					}
				}

				// select the last selected session
				auto selected_editor_id = info.get<EditorId>("project.edition.selected", EditorId::INVALID);
				if( is_valid( selected_editor_id ) )
				{
					UTILCPP_LOG << "Loaded session to select (if available) : [" << selected_editor_id << "]";
					select_editor( selected_editor_id );
				}
				else
				{
					if( !m_edit_sessions.empty() )
					{
						const auto last_editor_id = m_edit_sessions.back()->id();
						UTILCPP_LOG << "Selected session not found, will select : [" << last_editor_id << "]";
						select_editor( last_editor_id ); // select the last session registered if none selected found
					}
					else
					{
						UTILCPP_LOG << "Selected session not found, no other session to select.";
					}
					
				}
				
			}
			else
			{
				UTILCPP_LOG << "No editor for this project.";
			}

			

		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project's editor loading : \n" << boost::diagnostic_information(e);
		}

		
	}


	Project::~Project()
	{
		// THIS IS TEMPORARY : should be replaced by proper edition selection clearing ?

	}


	void Project::relocate( const bfs::path& new_filepath )
	{
		// TODO : add some checks!
		// TODO : move the files in the new location?
		m_location = new_filepath;
		m_directory_path = m_location.parent_path();

		UTILCPP_ASSERT( bfs::is_regular_file( m_location ), "Tried to create a project with an invalid file path! Path : " << m_location )
		UTILCPP_ASSERT( bfs::is_directory( m_directory_path ), "Wow, what's wrong with that project's directory? Path : " << m_directory_path )

	}

	void Project::rename( const std::string& new_name )
	{
		if( new_name.empty()  )
		{
			UTILCPP_LOG_ERROR << "Tried to rename project " << m_name << " to \"" << new_name << "\" : invalid!";
			return;
		}

		m_name = new_name;
	}

	bool Project::save()
	{
		using namespace boost::property_tree;

		// fill it with properties that needs to be saved
		ptree info;

		info.put( "project.name", name() );

		foreach_sequence( [&]( const Sequence& sequence )
		{ 
			info.add( "project.sequences.sequence", sequence.location().generic_string() );
		});

		foreach_edition( [&]( const Editor& editor )
		{ 
			info.add( "project.edition.session", editor.id() );
		});

		if( m_selected_session )
			info.add( "project.edition.selected",  m_selected_session->id() );

		// TODO : add other information here
		// TODO : manage errors differently

		try
		{
			namespace bfs = boost::filesystem;
			const auto directory_path = m_location.parent_path();

			// make sure the directory is available
			if( !bfs::is_directory( directory_path ) )
			{
				bfs::create_directories( directory_path );
			}
			
			bfs::ofstream filestream( m_location );
			write_xml( filestream, info );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR <<  boost::diagnostic_information(e);
			return false;
		}

		for( auto& sequence : m_sequences )
		{ 
			sequence->save(); 
		}

		for( auto& editor : m_edit_sessions )
		{ 
			const auto& file_path = directory_path() / path::EDITION_SESSION_FILE( to_string( editor->id() ) );
			editor->save( file_path ); 
		}

		return true;
	}

	void Project::foreach_sequence( std::function< void ( const Sequence& sequence )> func ) const
	{
		for( const auto& a_sequence : m_sequences )
			func( *a_sequence );
	}

	void Project::foreach_edition( std::function< void ( const Editor& editor )> func ) const
	{
		for( const auto& a_session : m_edit_sessions )
			func( *a_session );
	}

	bool Project::new_sequence( const SequenceInfo& info )
	{
		auto sequence = new Sequence( *this, info );
		
		add_sequence( std::unique_ptr<Sequence>( sequence ) );
		/* TODO: emit */ sequence_created( *sequence );

		if( info.is_edition_requested )
		{
			EditorInfo editor_info;
			editor_info.name = sequence->name();
			editor_info.sequence_id = sequence->id();
			return new_edition( editor_info );
		}

		return true;
	}


	bool Project::new_edition( const EditorInfo& editor_info )
	{
		Sequence* sequence = find_sequence( editor_info.sequence_id );
		
		if( sequence )
		{
			auto session = std::unique_ptr< Editor >( new Editor( *this, *sequence, editor_info.name ) );
			/* TODO: emit */ editor_created( *session ); // notify the world!

			add_edition( std::move(session) );

			return true;
		}

		return false;
	}



	void Project::add_sequence( std::unique_ptr<Sequence> sequence )
	{
		UTILCPP_ASSERT_NOT_NULL( sequence );
		m_sequences.push_back( std::move( sequence ) );
	}


	void Project::add_edition( std::unique_ptr<Editor> edition )
	{
		UTILCPP_ASSERT_NOT_NULL( edition );
		
		const bool is_edition_begin = m_edit_sessions.empty();

		m_edit_sessions.push_back( std::move( edition ) );

		/* TODO: emit */ editor_begin( *m_edit_sessions.back() );

		if( is_edition_begin )
			/* TODO: emit */ edition_begin();

	}

	Sequence* Project::find_sequence( const SequenceId& sequence_id )
	{
		if( m_sequences.empty() )
			return nullptr;

		auto find_it = std::find_if( m_sequences.begin(), m_sequences.end()
			, [&]( const std::unique_ptr<Sequence>& sequence ){ return sequence->id() == sequence_id; } );

		if( find_it != m_sequences.end() )
			return find_it->get();
		else
			return nullptr;
	}

	Editor* Project::find_edition( EditorId editor_id )
	{
		if( m_edit_sessions.empty() || !is_valid( editor_id ) )
			return nullptr;

		auto find_it = std::find_if( m_edit_sessions.begin(), m_edit_sessions.end()
			, [&]( const std::unique_ptr<Editor>& editor ){ return editor->id() == editor_id; } );

		if( find_it != m_edit_sessions.end() )
			return find_it->get();
		else
			return nullptr;
	}

	void Project::select_editor( const EditorId& editor_id )
	{
		Editor* editor = find_edition( editor_id );

		if( editor )
		{
			auto* previous_selected_session = selected_editor();

			m_selected_session = editor;

			if( previous_selected_session )
			{
				/* TODO: emit */ edition_deselected( *previous_selected_session );
			}

			UTILCPP_LOG << "Selected session [" << m_selected_session->id() << "] \"" << m_selected_session->name() << "\"";
			/* TODO: emit */ edition_selected( *selected_editor() );
		}

	}

	void Project::deselect_editor()
	{
		if( m_selected_session )
		{
			/* TODO: emit */ edition_deselected( *m_selected_session );
			m_selected_session = nullptr;
		}

	}

	void Project::close()
	{
		deselect_editor();

		// make sure that the world is notified by the closing of all edition sessions, without deleting them
		for( auto& session : m_edit_sessions )
		{
			/* TODO: emit */ editor_end( *session );
		}

		/* TODO: emit */ edition_end();
	}

	bool Project::delete_edition( EditorId editor_id )
	{
		auto editor = find_edition( editor_id );

		if( editor )
		{
			if( selected_editor() == editor )
			{
				deselect_editor();
			}
				
			try
			{
				auto save_filepath = editor->save_filepath();
				
				if( exists( save_filepath ) )
				{
					if( remove( save_filepath ) )
					{
						UTILCPP_LOG << "Removed editor filed : " << save_filepath;
					}
					else
					{
						UTILCPP_LOG << "Failed to remove editor file : " << save_filepath;
					}
				}
				
			}
			catch (const boost::exception& e)
			{
				UTILCPP_LOG_ERROR << "ERROR on deleting editor '" << editor->name() << "' save file : \n" << boost::diagnostic_information(e) 
					<< "'\nNote : The file will remain but the session will be removed from the Project.";
			}
			
			// now notify the world about the end of this session
			/* TODO: emit */ editor_end( *editor );
			/* TODO: emit */ editor_deleted( *editor );

			const auto editor_name = editor->name();

			// and delete it
			m_edit_sessions.erase( std::remove_if( begin(m_edit_sessions), end(m_edit_sessions), [&]( const std::unique_ptr<Editor>& session )
											{ return session->id() == editor_id; } )
											, m_edit_sessions.end() );
			
			UTILCPP_LOG << "Edition session \"" << editor_name << "\" have been destroyed and removed from the Project";

			if( m_edit_sessions.empty() )
				/* TODO: emit */ edition_end();

			return true;
		}
		else return false;
	}





}
}
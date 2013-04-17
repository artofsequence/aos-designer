#include "core/project.hpp"

#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "utilcpp/assert.hpp"

#include "core/projectinfos.hpp"
#include "core/sequenceinfos.hpp"
#include "core/sequence.hpp"
#include "core/editionsession.hpp"
#include "view/dialogs.hpp"
#include "paths.hpp"

namespace aosd
{
namespace core
{

	Project::Project( const ProjectInfos& infos )
		: m_location( infos.location )
		, m_name( infos.name )
		, m_directory_path( infos.location.parent_path() )
		, m_selected_session( nullptr )
	{
		UTILCPP_ASSERT( is_valid(infos), "Tried to construct a Project with invalid project infos!" );
	}

	Project::Project( const bfs::path& project_file_path )
		: m_location( project_file_path )
		, m_directory_path( project_file_path.parent_path() )
		, m_selected_session( nullptr )
	{
		UTILCPP_ASSERT( !project_file_path.empty(), "Tried to construct a Project at an empty path!" );
		UTILCPP_ASSERT( bfs::is_regular_file( m_location ), "Tried to create a project with an invalid file path! Path : " << m_location )
		UTILCPP_ASSERT( bfs::is_directory( m_directory_path ), "Wow, what's wrong with that project's directory? Path : " << m_directory_path )

		// THINK : make it  a throwing test?
		UTILCPP_ASSERT( boost::filesystem::exists( project_file_path ), "Tried to construct a Project with a path that don't exist!" ); 

		// THINK : move that in a separate function?
		using namespace boost::property_tree;
		ptree infos;

		try
		{
			bfs::ifstream filestream( project_file_path );			
			read_xml( filestream, infos );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project file loading : \n" << boost::diagnostic_information(e);
		}

		try
		{
			m_name = infos.get<std::string>( "project.name" );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project's properties reading : \n" << boost::diagnostic_information(e);
		}

		try
		{
			auto sequences = infos.get_child( "project.sequences", ptree() );

			if( !sequences.empty() )
			{
				std::for_each( sequences.begin(), sequences.end(), [&]( const std::pair< std::string, ptree >& sequence_info )
				{
					if( sequence_info.first == "sequence" )
					{
						const bfs::path sequence_location = sequence_info.second.get_value<std::string>();
						add_sequence( std::unique_ptr<Sequence>( new Sequence( *this, sequence_location ) ) );

						UTILCPP_LOG << "Loaded Sequence : " << m_sequences.back()->name() << " [" << m_sequences.back()->id() << "]";
					}
					else
					{
						UTILCPP_LOG_ERROR << "Found an unknown tag! Should be \"sequence\" instead of \"" << sequence_info.first << "\"";
					}



				});
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
			auto edition_sessions = infos.get_child( "project.edition", ptree() );

			if( !edition_sessions.empty() )
			{
				std::for_each( edition_sessions.begin(), edition_sessions.end(), [&]( const std::pair< std::string, ptree >& edition_session )
				{
					if( edition_session.first == "session" )
					{
						EditionSessionId session_id;
						try
						{
							 session_id = edition_session.second.get_value<EditionSessionId>();
						}
						catch (const boost::exception& e)
						{
							UTILCPP_LOG_ERROR << "Failed to interpret edition session id : [" << edition_session.second.get_value<std::string>() << "] : \n" << boost::diagnostic_information(e);
						}
						
						if( is_valid( session_id ) )
						{
							try
							{
								const bfs::path session_file_location = directory_path() / path::EDITION_SESSION_FILE( session_id );
								auto session = std::unique_ptr<EditionSession>( new EditionSession( *this, session_file_location ) );
								if( session->is_valid() )
								{
									add_edition( std::move(session) );

									UTILCPP_LOG << "Loaded edition session : [" << session_id << "]";
								}
								
							}
							catch( const boost::exception& e )
							{
								UTILCPP_LOG_ERROR << "Failed to load edition session [" << session_id << "] : \n" << boost::diagnostic_information(e);
							}
						}
						else
						{
							UTILCPP_LOG_ERROR << "Invalid session id found - certainly due to some problem in a previous working session.";
						}
						
					}
					else if( edition_session.first != "selected" )
					{
						UTILCPP_LOG_ERROR << "Found an unknown tag! Should be \"session\" instead of \"" << edition_session.first << "\"";
					}
				});

				// select the last selected session
				auto selected_session_id = infos.get<EditionSessionId>("project.edition.selected", EditionSessionId_INVALID);
				if( is_valid( selected_session_id ) )
				{
					UTILCPP_LOG << "Loaded session to select (if available) : [" << selected_session_id << "]";
					select_edition_session( selected_session_id );
				}
				else
				{
					if( !m_edit_sessions.empty() )
					{
						const auto last_session_id = m_edit_sessions.back()->id();
						UTILCPP_LOG << "Selected session not found, will select : [" << last_session_id << "]";
						select_edition_session( last_session_id ); // select the last session registered if none selected found
					}
					else
					{
						UTILCPP_LOG << "Selected session not found, no other session to select.";
					}
					
				}
				
			}
			else
			{
				UTILCPP_LOG << "No edition session for this project.";
			}

			

		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR << "ERROR on Project's edition session loading : \n" << boost::diagnostic_information(e);
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
		ptree infos;

		infos.put( "project.name", name() );

		foreach_sequence( [&]( const Sequence& sequence )
		{ 
			infos.add( "project.sequences.sequence", sequence.location().generic_string() );
		});

		foreach_edition( [&]( const EditionSession& edition_session )
		{ 
			infos.add( "project.edition.session", edition_session.id() );
		});

		if( m_selected_session )
			infos.add( "project.edition.selected",  m_selected_session->id() );

		// TODO : add other informations here
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
			write_xml( filestream, infos );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR <<  boost::diagnostic_information(e);
			return false;
		}

		std::for_each( m_sequences.begin(), m_sequences.end(), [&]( std::unique_ptr<Sequence>& sequence )
		{ 
			sequence->save(); 
		});

		std::for_each( m_edit_sessions.begin(), m_edit_sessions.end(), [&]( std::unique_ptr<EditionSession>& edition_session )
		{ 
			const auto& file_path = directory_path() / path::EDITION_SESSION_FILE( edition_session->id() );
			edition_session->save( file_path ); 
		});

		return true;
	}

	void Project::foreach_sequence( std::function< void ( const Sequence& sequence )> func ) const
	{
		std::for_each( m_sequences.begin(), m_sequences.end(), [&]( const std::unique_ptr<Sequence>& a_sequence ){ func(*a_sequence); } );
	}

	void Project::foreach_edition( std::function< void ( const EditionSession& edition_session )> func ) const
	{
		std::for_each( m_edit_sessions.begin(), m_edit_sessions.end(),  [&]( const std::unique_ptr<EditionSession>& a_session ){ func(*a_session); } );
	}

	bool Project::new_sequence( const SequenceInfos& infos )
	{
		auto sequence = new Sequence( *this, infos );
		
		add_sequence( std::unique_ptr<Sequence>( sequence ) );
		emit sequence_created( *sequence );

		if( infos.is_edition_requested )
		{
			EditionSessionInfos session_infos;
			session_infos.name = sequence->name();
			session_infos.sequence_id = sequence->id();
			return new_edition( session_infos );
		}

		return true;
	}

	bool Project::new_sequence()
	{
		// request the new sequence infos
		const SequenceInfos infos = view::request_new_sequence_infos();

		// create and register the sequence
		if( is_valid( infos ) ) 
			return new_sequence( infos );
		else 
			return false;

	}

	bool Project::new_edition( const EditionSessionInfos& session_infos )
	{
		Sequence* sequence = find_sequence( session_infos.sequence_id );
		
		if( sequence )
		{
			auto session = std::unique_ptr< EditionSession >( new EditionSession( *this, *sequence, session_infos.name ) );
			emit edition_session_created( *session ); // notify the world!

			add_edition( std::move(session) );

			return true;
		}

		return false;
	}

	bool Project::new_edition()
	{
		// request the new edition session
		const EditionSessionInfos infos = view::request_new_edition_session_infos();

		// create and register the sequence
		if( is_valid( infos ) ) 
			return new_edition( infos );
		else 
			return false;
	}


	void Project::add_sequence( std::unique_ptr<Sequence> sequence )
	{
		UTILCPP_ASSERT_NOT_NULL( sequence );
		m_sequences.push_back( std::move( sequence ) );
	}


	void Project::add_edition( std::unique_ptr<EditionSession> edition )
	{
		UTILCPP_ASSERT_NOT_NULL( edition );
		
		const bool is_edition_begin = m_edit_sessions.empty();

		m_edit_sessions.push_back( std::move( edition ) );

		emit edition_session_begin( *m_edit_sessions.back() );

		if( is_edition_begin )
			emit edition_begin();

	}

	Sequence* Project::find_sequence( const SequenceId& sequence_id )
	{
		if( m_sequences.empty() )
			return nullptr;

		auto find_it = std::find_if( m_sequences.begin(), m_sequences.end(), [&]( const std::unique_ptr<Sequence>& sequence ){ return sequence->id() == sequence_id; } );

		if( find_it != m_sequences.end() )
			return find_it->get();
		else
			return nullptr;
	}

	EditionSession* Project::find_edition( EditionSessionId session_id )
	{
		if( m_edit_sessions.empty() || !is_valid( session_id ) )
			return nullptr;

		auto find_it = std::find_if( m_edit_sessions.begin(), m_edit_sessions.end(), [&]( const std::unique_ptr<EditionSession>& edition_session ){ return edition_session->id() == session_id; } );

		if( find_it != m_edit_sessions.end() )
			return find_it->get();
		else
			return nullptr;
	}

	void Project::select_edition_session( const EditionSessionId& session_id )
	{
		EditionSession* edition_session = find_edition( session_id );

		if( edition_session )
		{
			auto* previous_selected_session = selected_edition_session();

			m_selected_session = edition_session;

			if( previous_selected_session )
			{
				emit edition_deselected( *previous_selected_session );
			}

			UTILCPP_LOG << "Selected session [" << m_selected_session->id() << "] \"" << m_selected_session->name() << "\"";
			emit edition_selected( *selected_edition_session() );
		}

	}

	void Project::deselect_edition_session()
	{
		if( m_selected_session )
		{
			emit edition_deselected( *m_selected_session );
			m_selected_session = nullptr;
		}

	}

	void Project::close()
	{
		deselect_edition_session();

		// make sure that the world is notified by the closing of all edition sessions, without deleting them
		std::for_each( begin(m_edit_sessions), end(m_edit_sessions), [&]( std::unique_ptr<EditionSession>& session )
		{
			emit edition_session_end( *session );
		});

		emit edition_end();
	}

	bool Project::delete_edition( EditionSessionId session_id )
	{
		auto edition_session = find_edition( session_id );

		if( edition_session )
		{
			if( selected_edition_session() == edition_session )
			{
				deselect_edition_session();
			}
				
			try
			{
				auto save_filepath = edition_session->save_filepath();
				
				if( exists( save_filepath ) )
				{
					if( remove( save_filepath ) )
					{
						UTILCPP_LOG << "Removed edition session filed : " << save_filepath;
					}
					else
					{
						UTILCPP_LOG << "Failed to remove edition session file : " << save_filepath;
					}
				}
				
			}
			catch (const boost::exception& e)
			{
				UTILCPP_LOG_ERROR << "ERROR on deleting edition session '" << edition_session->name() << "' save file : \n" << boost::diagnostic_information(e) 
					<< "'\nNote : The file will remain but the session will be removed from the Project.";
			}
			
			// now notify the world about the end of this session
			emit edition_session_end( *edition_session );
			emit edition_session_deleted( *edition_session );

			const auto session_name = edition_session->name();

			// and delete it
			m_edit_sessions.erase( std::remove_if( begin(m_edit_sessions), end(m_edit_sessions), [&]( const std::unique_ptr<EditionSession>& session )
											{ return session->id() == session_id; } )
											, m_edit_sessions.end() );
			
			UTILCPP_LOG << "Edition session \"" << session_name << "\" have been destroyed and removed from the Project";

			if( m_edit_sessions.empty() )
				emit edition_end();

			return true;
		}
		else return false;
	}





}
}
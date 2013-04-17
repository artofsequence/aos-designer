#include "core/editionsession.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include "utilcpp/assert.hpp"
#include "utilcpp/log.hpp"

#include "core/sequence.hpp"
#include "core/project.hpp"
#include "aoslcpp/sequenceinterpreter.hpp"
#include "paths.hpp"

namespace aosd
{
namespace core
{
	

	EditionSession::EditionSession( const Project& project, const Sequence& sequence, const std::string& name )
		: m_sequence( &sequence )
		, m_project( project )
		, m_interpreter( sequence.make_interpreter() )
		, m_id( to_string( boost::uuids::random_generator()() ) )
		, m_sequence_id( sequence.id() )
		, m_name( name )
	{
		UTILCPP_ASSERT_NOT_NULL( m_sequence ); // TODO : replace this by an throwing an exception at runtime
	}

	EditionSession::EditionSession( const Project& project, const bfs::path& file_path )
		: m_project( project )
		, m_sequence( nullptr )
		, m_id( EditionSessionId_INVALID )
		, m_save_filepath( file_path )
	{
		using namespace boost::property_tree;

		try
		{
			bfs::ifstream file_stream( file_path );

			if( file_stream.fail() )
			{
				UTILCPP_LOG_ERROR << "Failed to open file " << file_path;
				return;
			}

			ptree infos;
			read_xml( file_stream, infos );

			m_id = infos.get<EditionSessionId>( "edition_session.id" );
			m_name = infos.get<std::string>( "edition_session.name" );

			m_sequence_id = infos.get<SequenceId>( "edition_session.sequence", "NONE" );
			if( !m_sequence_id.empty() && m_sequence_id != "NONE" )
			{
				m_sequence = project.find_sequence( m_sequence_id );
				if( m_sequence )
				{
					m_interpreter = m_sequence->make_interpreter();

					// TODO : inject the path in the interpreter, maybe in another (public) function?
				}
				else
				{
					UTILCPP_LOG_ERROR << "Sequence id not found in the project!";
				}
			}
			else
			{
				UTILCPP_LOG_ERROR << "No valid sequence id!";
			}

		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR <<  boost::diagnostic_information(e);
		}
		

	}


	void EditionSession::save( const bfs::path& file_path )
	{
		UTILCPP_ASSERT( m_sequence ? m_sequence_id == m_sequence->id() : true, "Edition session isn't in sync with the sequence id!" )

		using namespace boost::property_tree;

		ptree infos;

		// write the sequence id
		infos.put( "edition_session.id", id() );
		infos.put( "edition_session.name", name() );
		infos.put( "edition_session.sequence", m_sequence ? m_sequence->id() : "NONE" );

		// write the path taken in the sequence
		if( m_interpreter )
		{
			m_interpreter->path().for_each_step( [&]( const aoslcpp::StoryPath::Step& step )
			{
				//infos.put( "edition_session.steps.move", step.move );
				//infos.put( "edition_session.steps.stage", step.stage );
			});
		}

		try
		{
			m_save_filepath = file_path;
			namespace bfs = boost::filesystem;
			bfs::ofstream file_stream( file_path );

			write_xml( file_stream, infos );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR <<  boost::diagnostic_information(e);
		}

	}

	

}
}
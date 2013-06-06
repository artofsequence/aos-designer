#include <aosdesigner/backend/editor.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/exception/diagnostic_information.hpp>

#include <utilcpp/assert.hpp>
#include <utilcpp/log.hpp>

#include <aoslcpp/sequenceinterpreter.hpp>

#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/paths.hpp>



namespace aosd {
namespace backend {
	
	Editor::Editor( const Project& project, const Sequence& sequence, const std::string& name )
		: m_sequence( &sequence )
		, m_project( project )
		, m_interpreter( sequence.make_interpreter() )
		, m_id( make_new_id<Editor>() )
		, m_sequence_id( sequence.id() )
		, m_name( name )
	{
		UTILCPP_ASSERT_NOT_NULL( m_sequence ); // TODO : replace this by an throwing an exception at runtime
	}

	Editor::Editor( const Project& project, const bfs::path& file_path )
		: m_project( project )
		, m_sequence( nullptr )
		, m_id( EditorId::INVALID )
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

			ptree info;
			read_xml( file_stream, info );

			m_id = info.get<EditorId>( "editor.id" );
			m_name = info.get<std::string>( "editor.name" );

			m_sequence_id = info.get<SequenceId>( "editor.sequence" );
			if( m_sequence_id.is_valid() )
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


	void Editor::save( const bfs::path& file_path )
	{
		UTILCPP_ASSERT( m_sequence ? m_sequence_id == m_sequence->id() : true, "Edition session isn't in sync with the sequence id!" )

		using namespace boost::property_tree;

		ptree info;

		// write the sequence id
		info.put( "editor.id", id() );
		info.put( "editor.name", name() );
		info.put( "editor.sequence", m_sequence ? m_sequence->id() : SequenceId::INVALID );

		// write the path taken in the sequence
		if( m_interpreter )
		{
			m_interpreter->path().for_each_step( [&]( const aoslcpp::StoryPath::Step& step )
			{
				//info.put( "editor.steps.move", step.move );
				//info.put( "editor.steps.stage", step.stage );
			});
		}

		try
		{
			m_save_filepath = file_path;
			namespace bfs = boost::filesystem;
			bfs::ofstream file_stream( file_path );

			write_xml( file_stream, info );
		}
		catch( const boost::exception& e )
		{
			UTILCPP_LOG_ERROR <<  boost::diagnostic_information(e);
		}

	}

	

}}
#include "core/sequence.hpp"

#include <string>

#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/algorithm/string.hpp>

#include "utilcpp/assert.hpp"

#include "aosl/aosl.hpp"
#include "aoslcpp/algorithm/edition.hpp"

#include "core/project.hpp"

#include "paths.hpp"

namespace aosd
{
namespace core
{

	Sequence::Sequence( const Project& project, const SequenceInfos& infos )
		: m_project( project )
		, m_name( infos.name )
		, m_location( infos.location )
		, m_sequence( aoslcpp::make_empty_sequence( infos.name, infos.canvas_width, infos.canvas_height ) )
	{
		if( m_sequence )
		{
			m_id = m_sequence->id();
		}
		
	}

	Sequence::Sequence( const Project& project, const boost::filesystem::path sequence_file_path )
		: m_project( project )
		, m_location( sequence_file_path )
	{
		xml_schema::Properties properties;
		properties.schema_location( aosl::AOSL_XML_NAMESPACE_NAME, path::AOSL_XSD_FILE.string() );

		boost::filesystem::ifstream filestream( full_location() );
		try
		{
			auto sequence = aosl::parse_sequence( filestream, 0, properties );
			m_sequence.reset( sequence.release() );
		}
		catch( const ::xsd::cxx::tree::parsing< char >& e )
		{
			UTILCPP_LOG_ERROR << e.what() << "\nDiagnostic : ";
			
			std::for_each( e.diagnostics().begin(), e.diagnostics().end(), []( const xsd::cxx::tree::error<char>& err )
			{
				UTILCPP_LOG_ERROR << "\n " << err;
			});
			
		}
		
		if( m_sequence )
		{
			m_name = m_sequence->name();
			m_id = m_sequence->id();

			m_library.update( m_sequence->library() );
		}
		else
		{
			m_name = "UNREADABLE SEQUENCE";
			m_id = "";
		}

	}

	Sequence::~Sequence()
	{

	}

	bool Sequence::save()
	{
		if( m_sequence )
		{

			const auto sequence_file_path = full_location();
			const auto sequence_directory = sequence_file_path.parent_path();
			if( ! boost::filesystem::is_directory( sequence_directory ) )
			{
				boost::filesystem::create_directories( sequence_directory );
			}

			xml_schema::NamespaceInfomap namespace_infos;
			namespace_infos["aos"].name = aosl::AOSL_XML_NAMESPACE_NAME;

			boost::filesystem::ofstream filestream( sequence_file_path );
			aosl::serialize_sequence( filestream, *m_sequence, namespace_infos );
		
			return true;

		}
		else
			return false;
	}

	boost::filesystem::path Sequence::full_location() const
	{
		return m_project.directory_path() / location();
	}

	std::unique_ptr<aoslcpp::SequenceInterpreter> Sequence::make_interpreter() const
	{
		if( m_sequence )
		{
			return std::unique_ptr<aoslcpp::SequenceInterpreter>( new aoslcpp::SequenceInterpreter( *m_sequence ) );
		}

		return std::unique_ptr<aoslcpp::SequenceInterpreter>();
	}




}
}
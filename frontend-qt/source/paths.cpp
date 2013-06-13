#include "paths.hpp"

#include <boost/filesystem.hpp>

namespace aosd
{
namespace path
{
	const bfs::path	AOSL_XSD_FILE			= bfs::current_path() / "aosl.xsd";

	const std::string PROJECT_FILE_EXTENSION			= ".aosp";
	const std::string SEQUENCE_FILE_EXTENSION			= ".aosl";
	const std::string META_FILE_EXTENSION				= ".aosl";
	const std::string LIBRARY_FILE_EXTENSION			= ".aosl";
	const std::string EDITION_SESSION_FILE_EXTENSION	= ".aosd.session";


	const bfs::path DEFAULT_PROJECTS_DIR	= bfs::current_path(); // TODO : replace this by the user directory
	const bfs::path PROJECT_LIBRARY_DIR		= "./library/";
	const bfs::path PROJECT_LIBRARY_FILE	= PROJECT_LIBRARY_DIR / "library.aosl";
	const bfs::path PROJECT_META_FILE		= "./meta.aosl";
	const bfs::path PROJECT_SEQUENCES_DIR	= "./sequences/";

	const bfs::path EDITION_SESSIONS_DIR = ".";

	const bfs::path LOG_FILE_DIR			= bfs::current_path() / "logs";
	
	bfs::path SEQUENCE_DIR( const std::string& sequence_codename )
	{
		// TODO : add some checks
		return PROJECT_SEQUENCES_DIR / sequence_codename;
	}

	bfs::path SEQUENCE_FILE( const std::string& sequence_codename )
	{
		// TODO : add some checks
		return SEQUENCE_DIR( sequence_codename ) / (sequence_codename + SEQUENCE_FILE_EXTENSION );
	}

	bfs::path PROJECT_FILE( const std::string& project_codename )
	{
		// TODO : add some checks
		return project_codename + PROJECT_FILE_EXTENSION;
	}


	bfs::path EDITION_SESSION_FILE( const std::string& editor_id )
	{
		return EDITION_SESSIONS_DIR / ("edit-" + editor_id + EDITION_SESSION_FILE_EXTENSION ) ;
	}


	bfs::path GENERATE_PROJECT_FILE( const bfs::path& directory, const std::string& project_codename )
	{
		return directory / project_codename / ( project_codename + PROJECT_FILE_EXTENSION );
	}




}
}

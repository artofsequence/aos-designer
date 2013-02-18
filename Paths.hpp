#ifndef HGUARD_AOSD_CORE_PATHS_HPP__
#define HGUARD_AOSD_CORE_PATHS_HPP__
#pragma once

#include <string>
#include <boost/filesystem/path.hpp>

namespace aosd
{
namespace path
{
	namespace bfs = boost::filesystem;

	/// XSD file used for aosl files validation.
	extern const bfs::path AOSL_XSD_FILE;

	/// Extension of projects files.
	extern const std::string PROJECT_FILE_EXTENSION;

	/// Extension of sequence files.
	extern const std::string SEQUENCE_FILE_EXTENSION;

	/// Extension of meta files.
	extern const std::string META_FILE_EXTENSION;

	/// Extension of library files.
	extern const std::string LIBRARY_FILE_EXTENSION;

	/// Extension of Edition session files.
	extern const std::string EDITION_SESSION_FILE_EXTENSION;

	/// Default directory to look in when we start looking for project directories.
	extern const bfs::path DEFAULT_PROJECTS_DIR;

	/// Common library directory where all it's resources will be contained.
	extern const bfs::path PROJECT_LIBRARY_DIR;

	/// Common library definition file.
	extern const bfs::path PROJECT_LIBRARY_FILE;

	/// Meta informations common to all the sequences.
	extern const bfs::path PROJECT_META_FILE;

	/// Directory containing the project's sequences.
	extern const bfs::path PROJECT_SEQUENCES_DIR;

	/// Directory that will contain the log file(s).
	extern const bfs::path LOG_FILE_DIR;

	/// Directory that will contain edition session files.
	extern const bfs::path EDITION_SESSIONS_DIR;

	/// Generate the path of a sequence directory.
	bfs::path SEQUENCE_DIR( const std::string& sequence_codename );

	/// Generate the path of a sequence file definition.
	bfs::path SEQUENCE_FILE( const std::string& sequence_codename );

	/// Project infos file, defining the whole project.
	bfs::path PROJECT_FILE( const std::string& project_codename );
	
	/// Edition session infos file, defining a path in a walk in a sequence.
	bfs::path EDITION_SESSION_FILE( const std::string& edition_session_id );

	/// Generate a full path of for a (fictive) project file given it's codename and the directory where to find the project's folder.
	bfs::path GENERATE_PROJECT_FILE( const bfs::path& directory, const std::string& project_codename );


}
}


#endif

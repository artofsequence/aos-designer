#ifndef HGUARD_AOSD_VIEW_DIALOGS_HPP__
#define HGUARD_AOSD_VIEW_DIALOGS_HPP__
#pragma once

#include <boost/filesystem/path.hpp>

#include <aosdesigner/backend/projectinfos.hpp>
#include <aosdesigner/backend/sequenceinfos.hpp>
#include <aosdesigner/backend/editionsessioninfos.hpp>

namespace aosd
{
namespace view
{
	namespace bfs = boost::filesystem;

	/** Request a directory path for a new project to the user by showing to the user a directory search window.
		@param default_path Default path to start the search at.
		@return The path of the directory selected by the user or an empty path if the user canceled the search.
	*/
	bfs::path request_new_project_path( bfs::path default_path = "" );

	/** Request a project path to the user by showing to the user a file search window.
		@param default_path Default path to start the search at.
		@return The path of the project selected by the user or an empty path if the user canceled the search.
	*/
	bfs::path request_project_path( bfs::path default_path = "" );

	/** Show the welcome screen to the user.
	*/
	void show_welcome_screen();

	/** Show the dialog to create a new project. */
	backend::ProjectInfos request_new_project_infos();

	/** Show the dialog to create a new sequence. */
	backend::SequenceInfos request_new_sequence_infos();

	/** Show the dialog to create a new edition session. */
	backend::EditionSessionInfos request_new_edition_session_infos();

}
}


#endif
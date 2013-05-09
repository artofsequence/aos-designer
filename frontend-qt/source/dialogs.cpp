#include "view/dialogs.hpp"

#include <QFileDialog>
#include <QObject>

#include "view/dialog/welcomescreen.hpp"
#include "view/dialog/newprojectdialog.hpp"
#include "view/dialog/newsequencedialog.hpp"
#include "view/dialog/neweditionsessiondialog.hpp"
#include "paths.hpp"

namespace aosd
{
namespace view
{

	void show_welcome_screen()
	{
		// TODO : reuse the dialog instead of re-creating it each time
		std::unique_ptr<WelcomeScreen> screen( new WelcomeScreen() );
		screen->exec();
	}

	bfs::path request_new_project_path( bfs::path default_path )
	{
		if( default_path.empty() )
			default_path = path::DEFAULT_PROJECTS_DIR;

		return bfs::path( QFileDialog::getExistingDirectory( nullptr
															, QObject::tr("New AOS Designer Project Location")
															, QString::fromStdString( default_path.string() )
															).toStdString() );
	}


	bfs::path request_project_path( bfs::path default_path )
	{
		if( default_path.empty() )
			default_path = path::DEFAULT_PROJECTS_DIR;

		return bfs::path( QFileDialog::getOpenFileName( nullptr
														, QObject::tr( "Open AOS Designer Project" )
														, QString::fromStdString( default_path.string() )
														, QObject::tr( "AOS Designer Project (*.aosp)" )
														).toStdString() );
	}

	template< class InfoType, class DialogType>
	InfoType request_infos()
	{
		std::unique_ptr<DialogType> dialog( new DialogType() );
		if( dialog->exec() )
			return dialog->infos();
		else
			return InfoType();
	}

	backend::ProjectInfos request_new_project_infos()
	{
		return request_infos< backend::ProjectInfos, NewProjectDialog >();
	}

	backend::SequenceInfos request_new_sequence_infos()
	{
		return request_infos< backend::SequenceInfos, NewSequenceDialog >();
	}

	backend::EditionSessionInfos request_new_edition_session_infos()
	{
		return request_infos< backend::EditionSessionInfos, NewEditionSessionDialog >();
	}

}
}
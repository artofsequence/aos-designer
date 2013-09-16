#include "dialogs.hpp"

#include <QFileDialog>
#include <QObject>

#include "dialog/welcomescreen.hpp"
#include "dialog/newprojectdialog.hpp"
#include "dialog/newsequencedialog.hpp"
#include "dialog/neweditionsessiondialog.hpp"
#include <aosdesigner/backend/paths.hpp>

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
	InfoType request_info()
	{
		std::unique_ptr<DialogType> dialog( new DialogType() );
		if( dialog->exec() )
			return dialog->info();
		else
			return InfoType();
	}

	backend::ProjectInfo request_new_project_info()
	{
		return request_info< backend::ProjectInfo, NewProjectDialog >();
	}

	backend::SequenceInfo request_new_sequence_info()
	{
		return request_info< backend::SequenceInfo, NewSequenceDialog >();
	}

	backend::EditorInfo request_new_editor_info()
	{
		return request_info< backend::EditorInfo, NewEditorDialog >();
	}

}
}
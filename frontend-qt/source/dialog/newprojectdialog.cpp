#include "newprojectdialog.hpp"

#include <QRegExpValidator>

#include "ui_newprojectdialog.h"
#include "view/dialogs.hpp"
#include "paths.hpp"

namespace aosd
{
namespace view
{
	

	NewProjectDialog::NewProjectDialog()
		: m_ui( new Ui::NewProjectDialog() )
	{
		m_ui->setupUi( this );

		// interactions
		connect( m_ui->button_cancel			, SIGNAL( clicked() )					, this		, SLOT( reject() )				);
		connect( m_ui->button_create			, SIGNAL( clicked() )					, this		, SLOT( create_project() )		);
		connect( m_ui->button_find_location		, SIGNAL( clicked() )					, this		, SLOT( find_location() )		);
		
		connect( m_ui->edit_project_name		, SIGNAL( textChanged(const QString&) )	, this		, SLOT( update_codename() )		);
		connect( m_ui->edit_codename			, SIGNAL( textChanged(const QString&) )	, this		, SLOT( update_project_file() ) );
		connect( m_ui->edit_dir_location		, SIGNAL( textChanged(const QString&) )	, this		, SLOT( update_project_file() ) );

		// set the validators
		auto* codename_validator = new QRegExpValidator( QRegExp("[A-Za-z0-9_]+"), this ); // TODO : later, allow any OS valid characters but no spaces.
		m_ui->edit_codename->setValidator( codename_validator );

		// set a default values
		m_ui->edit_project_name->setText( tr("My Project") );
		m_ui->edit_dir_location->setText( QString::fromStdString( path::DEFAULT_PROJECTS_DIR.string() ) );
		
		m_ui->edit_project_file_location->setReadOnly( true );


	}

	NewProjectDialog::~NewProjectDialog()
	{

	}

	void NewProjectDialog::find_location()
	{
		const bfs::path try_dir( m_ui->edit_dir_location->text().toStdString() );
		auto location = request_new_project_path( try_dir );
		if( !location.empty() )
		{
			m_ui->edit_dir_location->setText( QString::fromStdString(location.string()) );
		}
	}

	void NewProjectDialog::create_project()
	{
		// TODO : check that the names are filled
		if( !m_ui->edit_dir_location->text().isEmpty() 
		&&	!m_ui->edit_project_name->text().isEmpty() 
		)
		{
			// TODO : check that the location is valid
			// TODO : launch the creation of the project
			accept();
		}
		else
		{
			// TODO : notify the user?
		}
		
	}

	void NewProjectDialog::update_codename()
	{
		// TODO : factorize that!!
		const auto name = m_ui->edit_project_name->text();
		auto codename = name;
		
		codename = codename.trimmed();
		codename.replace( QRegExp( "\\s+" ), "_" );
		codename.replace( QRegExp( "\\W+" ), "" );

		m_ui->edit_codename->setText( codename );
	}


	core::ProjectInfo NewProjectDialog::info()
	{
		
		const auto location = m_ui->edit_dir_location->text();
		const auto codename = m_ui->edit_codename->text();
		const auto name = m_ui->edit_project_name->text();

		core::ProjectInfo info;
		if( !( location.isEmpty() || codename.isEmpty() ) )
		{
			info.location = path::GENERATE_PROJECT_FILE( boost::filesystem::path( location.toStdString() ), codename.toStdString() );
		}

		info.name = name.toStdString();
		
		return info;
	}

	void NewProjectDialog::update_project_file()
	{
		auto dir_location = m_ui->edit_dir_location->text();
		auto codename = m_ui->edit_codename->text();
		if( ! ( dir_location.isEmpty() || codename.isEmpty() )  )
		{
			namespace bsf = boost::filesystem;
			bfs::path directory_path = dir_location.toStdString();
			bfs::path project_file_path =  path::GENERATE_PROJECT_FILE( directory_path, codename.toStdString() );

			m_ui->edit_project_file_location->setText( QString::fromStdString( project_file_path.string() ) );
		}
	}

}
}
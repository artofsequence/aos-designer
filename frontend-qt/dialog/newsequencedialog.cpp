#include "newsequencedialog.hpp"

#include <QRegExpValidator>
#include <QDoubleValidator>

#include "ui_newsequencedialog.h"

#include "paths.hpp"

namespace aosd
{
namespace view
{
	NewSequenceDialog::NewSequenceDialog()
		: m_ui( new Ui::NewSequenceDialog() )
	{
		m_ui->setupUi( this );

		// interactions
		connect( m_ui->button_cancel			, SIGNAL( clicked() )					, this		, SLOT( reject() )				);
		connect( m_ui->button_create			, SIGNAL( clicked() )					, this		, SLOT( create_sequence() )		);
		connect( m_ui->edit_name				, SIGNAL( textChanged(const QString&) )	, this		, SLOT( update_codename() )		);
		
		// set the validators
		// TODO : put that validator somewhere accessible to other code
		auto* codename_validator = new QRegExpValidator( QRegExp("[A-Za-z0-9_]+"), this ); // TODO : later, allow any OS valid characters but no spaces.
		m_ui->edit_codename->setValidator( codename_validator );

		auto* width_validator = new QDoubleValidator(this);
		auto* height_validator = new QDoubleValidator(this);
		width_validator->setRange( 1, 0 );
		height_validator->setRange( 1, 0 );

		m_ui->edit_canvas_width->setValidator( width_validator );
		m_ui->edit_canvas_height->setValidator( height_validator );

		// set a default values
		m_ui->edit_name->setText( tr("Unnamed Sequence") );
		m_ui->edit_canvas_width->setText( "800" );
		m_ui->edit_canvas_height->setText( "600" );
		m_ui->check_create_edition->setChecked( true );
	}

	NewSequenceDialog::~NewSequenceDialog()
	{

	}

	core::SequenceInfos NewSequenceDialog::infos()
	{
		core::SequenceInfos infos;
		
		infos.name = m_ui->edit_name->text().toStdString();
		infos.location = path::SEQUENCE_FILE( m_ui->edit_codename->text().toStdString() );
		infos.canvas_width = m_ui->edit_canvas_width->text().toDouble();
		infos.canvas_height = m_ui->edit_canvas_height->text().toDouble();
		infos.is_edition_requested = m_ui->check_create_edition->isChecked();

		return infos;
	}

	void NewSequenceDialog::create_sequence()
	{
		// TODO : check that the names are filled
		if( !m_ui->edit_name->text().isEmpty() 
		&&	!m_ui->edit_canvas_width->text().isEmpty()
		&&	!m_ui->edit_canvas_height->text().isEmpty()
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

	void NewSequenceDialog::update_codename()
	{
		const auto name = m_ui->edit_name->text();
		auto codename = name;

		codename = codename.trimmed();
		codename.replace( QRegExp( "\\s+" ), "_" );
		codename.replace( QRegExp( "\\W+" ), "" );

		m_ui->edit_codename->setText( codename );
	}

}
}
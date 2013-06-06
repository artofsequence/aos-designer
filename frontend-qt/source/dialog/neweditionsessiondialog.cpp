#include "neweditionsessiondialog.hpp"

#include "core/context.hpp"
#include "core/project.hpp"
#include "core/sequence.hpp"
#include "core/editionsession.hpp"
#include "ui_neweditionsessiondialog.h"

namespace aosd
{
namespace view
{

	NewEditorDialog::NewEditorDialog()
		: m_ui( new Ui::NewEditorDialog() )
	{
		m_ui->setupUi( this );

		// interactions
		connect( m_ui->button_cancel			, SIGNAL( clicked() )					, this		, SLOT( reject() )				);
		connect( m_ui->button_create			, SIGNAL( clicked() )					, this		, SLOT( create_session() )		);
		connect( m_ui->selector_sequence		, SIGNAL( currentIndexChanged(int) )	, this		, SLOT( update_name() )			);
		
		fill_editor_selector();
		update_name();
	}

	NewEditorDialog::~NewEditorDialog()
	{

	}

	backend::EditorInfo NewEditorDialog::info() const
	{
		backend::EditorInfo editor_info;

		editor_info.name = m_ui->edit_name->text().toStdString();

		UTILCPP_ASSERT_NOT_NULL( m_ui->selector_sequence );
		auto& selector = *m_ui->selector_sequence;
		editor_info.sequence_id = selector.itemData( selector.currentIndex() ).toString().toStdString();

		return editor_info;
	}

	void NewEditorDialog::create_session()
	{
		// TODO : check that the names are filled
		if( !m_ui->edit_name->text().isEmpty() 
		&&	!m_ui->selector_sequence->currentText().isEmpty()
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

	void NewEditorDialog::fill_editor_selector()
	{
		const auto& context = core::Context::instance();

		if( !context.is_project_open() )
			return;

		const auto& project = context.current_project();

		auto& selector = *m_ui->selector_sequence;

		project.foreach_sequence( [&]( const core::Sequence& sequence )
		{
			selector.addItem( QString::fromStdString( sequence.name() ), QString::fromStdString( sequence.id() ) );
		});
		
	}

	void NewEditorDialog::update_name()
	{
		auto& selector = *m_ui->selector_sequence;
		core::SequenceId sequence_id = selector.itemData( selector.currentIndex() ).toString().toStdString();
		const auto sequence_name = selector.currentText().toStdString();
		std::size_t edition_count = 0;

		const auto& project = core::Context::instance().current_project();
		project.foreach_edition( [&]( const core::Editor& editor )
		{
			if( sequence_id == editor.sequence_id() )
			{
				++edition_count;
			}
		});


		std::stringstream proposed_name;
		proposed_name << sequence_name;
		
		if( edition_count > 0 )
			proposed_name << " (" << edition_count << ")";

		m_ui->edit_name->setText( QString::fromStdString( proposed_name.str() ) );

	}

}
}
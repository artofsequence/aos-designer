#include "NewEditionSessionDialog.hpp"

#include "core/Context.hpp"
#include "core/Project.hpp"
#include "core/Sequence.hpp"
#include "core/EditionSession.hpp"
#include "ui_NewEditionSessionDialog.h"

namespace aosd
{
namespace view
{

	NewEditionSessionDialog::NewEditionSessionDialog()
		: m_ui( new Ui::NewEditionSessionDialog() )
	{
		m_ui->setupUi( this );

		// interactions
		connect( m_ui->button_cancel			, SIGNAL( clicked() )					, this		, SLOT( reject() )				);
		connect( m_ui->button_create			, SIGNAL( clicked() )					, this		, SLOT( create_session() )		);
		connect( m_ui->selector_sequence		, SIGNAL( currentIndexChanged(int) )	, this		, SLOT( update_name() )			);
		
		fill_session_selector();
		update_name();
	}

	NewEditionSessionDialog::~NewEditionSessionDialog()
	{

	}

	core::EditionSessionInfos NewEditionSessionDialog::infos() const
	{
		core::EditionSessionInfos session_infos;

		session_infos.name = m_ui->edit_name->text().toStdString();

		UTILCPP_ASSERT_NOT_NULL( m_ui->selector_sequence );
		auto& selector = *m_ui->selector_sequence;
		session_infos.sequence_id = selector.itemData( selector.currentIndex() ).toString().toStdString();

		return session_infos;
	}

	void NewEditionSessionDialog::create_session()
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

	void NewEditionSessionDialog::fill_session_selector()
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

	void NewEditionSessionDialog::update_name()
	{
		auto& selector = *m_ui->selector_sequence;
		core::SequenceId sequence_id = selector.itemData( selector.currentIndex() ).toString().toStdString();
		const auto sequence_name = selector.currentText().toStdString();
		std::size_t edition_count = 0;

		const auto& project = core::Context::instance().current_project();
		project.foreach_edition( [&]( const core::EditionSession& edition_session )
		{
			if( sequence_id == edition_session.sequence_id() )
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
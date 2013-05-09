#include "changesview.hpp"

#include <QTreeView>

#include "core/editionsession.hpp"
#include "view/model/lastchangesmodel.hpp"

namespace aosd
{
namespace view
{


	ChangesView::ChangesView()
		: m_last_changes_view( new QTreeView() )
		, m_model_view_binder( *m_last_changes_view )
	{
		setWindowTitle( tr("Changes") );

		setWidget( m_last_changes_view.get() );
	}


	ChangesView::~ChangesView()
	{

	}


	void ChangesView::connect_edition( const backend::EditionSession& edition_session )
	{
		bool has_model = m_model_view_binder.load( edition_session.id() );
		if( !has_model )
		{
			begin_model( edition_session );
		}
	}

	void ChangesView::disconnect_edition( const backend::EditionSession& edition_session )
	{
		m_model_view_binder.unload();
	}

	void ChangesView::begin_edition_session( const backend::EditionSession& edition_session )
	{
		begin_model( edition_session );
	}

	void ChangesView::end_edition_session( const backend::EditionSession& edition_session )
	{
		end_model( edition_session );
	}

	void ChangesView::update_last_changes( const backend::EditionSession& edition_session )
	{
		if( edition_session.id() == m_model_view_binder.current_id() )
		{
			auto model = static_cast<LastChangesModel*>( m_model_view_binder.current_model() );
			model->update( edition_session.path(), edition_session.canvas(), edition_session.story() );
		}
	}

	void ChangesView::begin_model( const backend::EditionSession& edition_session )
	{
		auto model = std::unique_ptr<LastChangesModel>( new LastChangesModel() );
		model->update( edition_session.path(), edition_session.canvas(), edition_session.story() );
		m_model_view_binder.add( std::move(model), edition_session.id() );
		m_model_view_binder.load( edition_session.id() );
	}

	void ChangesView::end_model( const backend::EditionSession& edition_session )
	{
		m_model_view_binder.remove( edition_session.id() );
	}


}
}
#include "changesview.hpp"

#include <QTreeView>

#include <aosdesigner/backend/editor.hpp>
#include "model/lastchangesmodel.hpp"

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


	void ChangesView::connect_edition( const backend::Editor& editor )
	{
		bool has_model = m_model_view_binder.load( editor.id() );
		if( !has_model )
		{
			begin_model( editor );
		}
	}

	void ChangesView::disconnect_edition( const backend::Editor& editor )
	{
		m_model_view_binder.unload();
	}

	void ChangesView::begin_editor( const backend::Editor& editor )
	{
		begin_model( editor );
	}

	void ChangesView::end_editor( const backend::Editor& editor )
	{
		end_model( editor );
	}

	void ChangesView::update_last_changes( const backend::Editor& editor )
	{
		if( editor.id() == m_model_view_binder.current_id() )
		{
			auto model = static_cast<LastChangesModel*>( m_model_view_binder.current_model() );
			model->update( editor.path(), editor.canvas(), editor.story() );
		}
	}

	void ChangesView::begin_model( const backend::Editor& editor )
	{
		auto model = std::unique_ptr<LastChangesModel>( new LastChangesModel() );
		model->update( editor.path(), editor.canvas(), editor.story() );
		m_model_view_binder.add( std::move(model), editor.id() );
		m_model_view_binder.load( editor.id() );
	}

	void ChangesView::end_model( const backend::Editor& editor )
	{
		m_model_view_binder.remove( editor.id() );
	}


}
}
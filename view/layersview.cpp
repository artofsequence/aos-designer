#include "layersview.hpp"

#include "utilcpp/log.hpp"

#include <QSplitter>
#include <QTreeView>

#include "aosl/layer.hpp"
#include "core/editionsession.hpp"
#include "view/model/canvaslayersmodel.hpp"
#include "view/model/layerobjectsmodel.hpp"

namespace aosd
{
namespace view
{
	 
	LayersView::LayersView()
		: m_splitter( new QSplitter() )
		, m_layer_list_view( new QTreeView() )
		, m_layer_objects_view( new QTreeView() )
		, m_layer_model_binder( *m_layer_list_view )
		, m_layer_objects_model( new LayerObjectsModel() )
		, m_last_selected_layer( nullptr )
	{
		setWindowTitle(tr("Layers"));

		m_layer_objects_view->setModel( m_layer_objects_model.get() );
		connect( m_layer_list_view.get(), SIGNAL( clicked( const QModelIndex& ) ), this, SLOT( react_layer_clicked( const QModelIndex& ) ) );
		

		m_splitter->setOrientation( Qt::Vertical );
		m_splitter->addWidget( m_layer_list_view.get() );
		m_splitter->addWidget( m_layer_objects_view.get() );

		setWidget( m_splitter.get() );
	}

	LayersView::~LayersView()
	{
		m_layer_objects_view->setModel( nullptr );
	}

	void LayersView::connect_edition( const core::EditionSession& edition_session )
	{
		// first load the layer list
		bool has_model = m_layer_model_binder.load( edition_session.id() );
		if( !has_model )
		{
			begin_edition_session( edition_session );
			m_layer_model_binder.load( edition_session.id() );
		}
		
	}

	void LayersView::disconnect_edition( const core::EditionSession& edition_session )
	{
		m_layer_model_binder.unload();
		m_layer_objects_model->clear();
	}

	void LayersView::begin_edition_session( const core::EditionSession& edition_session )
	{
		m_layer_model_binder.add( std::unique_ptr<QAbstractItemModel>( new CanvasLayersModel( edition_session.canvas() ) ), edition_session.id() );
	}

	void LayersView::end_edition_session( const core::EditionSession& edition_session )
	{
		m_layer_model_binder.remove( edition_session.id() );
	}

	void LayersView::react_layer_clicked( const QModelIndex& layer_index )
	{
		update_layer_objects( layer_index );
	}

	void LayersView::update_layer_objects( const QModelIndex& layer_index )
	{
		auto layer = static_cast<const aosl::Layer*>( layer_index.internalPointer() );

		if( !m_last_selected_layer || m_last_selected_layer != layer )
		{
			m_layer_objects_model->update( *layer );
			m_last_selected_layer = layer;
		}
	}


}

}
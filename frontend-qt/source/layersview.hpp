#ifndef HGUARD_AOSD_VIEW_LAYERSVIEW_HPP__
#define HGUARD_AOSD_VIEW_LAYERSVIEW_HPP__
#pragma once

#include <memory>
#include <QModelIndex>

#include <aosdesigner/backend/id.hpp>

#include "editiontoolview.hpp"
#include "model/modelviewbinder.hpp"

class QTreeView;
class QSplitter;

namespace aosl
{
	class Layer;
}

namespace aosd
{
namespace view
{
	class LayerObjectsModel;
	
	/** Display the layers of a sequence, the associated objects and their state at the current story stage.
		Allow activating and deactivating layers for the current stage.
	**/
	class LayersView
		: public EditionToolView
	{

		Q_OBJECT
	public:
		
		LayersView();
		~LayersView();


	private slots:

		void react_layer_clicked( const QModelIndex& );

	private:

		std::unique_ptr< QSplitter > m_splitter;
		std::unique_ptr< QTreeView > m_layer_list_view;
		std::unique_ptr< QTreeView > m_layer_objects_view;

		ModelViewBinder<backend::EditionSessionId> m_layer_model_binder;
		std::unique_ptr< LayerObjectsModel > m_layer_objects_model;

		const aosl::Layer* m_last_selected_layer;

		void begin_edition_session( const backend::EditionSession& edition_session );
		void end_edition_session( const backend::EditionSession& edition_session );
		void connect_edition( const backend::EditionSession& edition_session );
		void disconnect_edition( const backend::EditionSession& edition_session );
		
		void update_layer_objects( const QModelIndex& );
		

	};


}
}

#endif

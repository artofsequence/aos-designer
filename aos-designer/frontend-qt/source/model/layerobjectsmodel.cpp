#include "layerobjectsmodel.hpp"

#include <utilcpp/assert.hpp>
		 
#include <aosl/layer.hpp>
#include <aosl/object.hpp>
#include <aosl/canvas.hpp>
#include <aoslcpp/algorithm/find.hpp>

namespace aosd
{
namespace view
{
	

	LayerObjectsModel::LayerObjectsModel()
	{

	}


	void LayerObjectsModel::update( const aosl::Layer& layer )
	{
		clear();
		
		beginResetModel();
		auto canvas = static_cast<const aosl::Canvas*>(layer._container()->_container());
		if( !canvas )
		{
			UTILCPP_LOG_ERROR << "Layer with no parent canvas!";
			return;
		}

		const auto& object_list = layer.object();
		
		for( const auto& object_ref : object_list )
		{
			auto object = aoslcpp::find_object( *canvas, object_ref.id() );
			if( object )
			{
				m_layer_objects.push_back( object );
			}
			else
			{
				UTILCPP_LOG_ERROR << "Couldn't find object '" << object_ref.id() << "' in the canvas. It was referenced by the layer '" << layer.id() << "'!";
			}
			
		}

		endResetModel();
	}

	void LayerObjectsModel::clear()
	{
		beginResetModel();
		m_layer_objects.clear();
		endResetModel();
	}

	QModelIndex LayerObjectsModel::index( int row, int column, const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( m_layer_objects.empty() )
			return QModelIndex();

		UTILCPP_ASSERT( !parent.isValid(), "Try to ge the index of child of layer's object but it's forbidden!" );

		return createIndex( row, column, (void*)m_layer_objects[ static_cast<size_t>(row) ] );
	}

	QModelIndex LayerObjectsModel::parent( const QModelIndex& index ) const
	{
		return QModelIndex();
	}

	Qt::ItemFlags LayerObjectsModel::flags( const QModelIndex& index ) const
	{
		return QAbstractItemModel::flags( index ) | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
	}


	QVariant LayerObjectsModel::data( const QModelIndex& index, int role /*= Qt::DisplayRole */ ) const
	{
		if( !index.isValid() || index.column() > 0 || m_layer_objects.empty() )
			return QVariant();

		auto object = m_layer_objects[ static_cast<size_t>( index.row() ) ];
		UTILCPP_ASSERT_NOT_NULL( object );

		switch( role )
		{
		case( Qt::DisplayRole ):
			{
				return QString::fromStdString( object->id() );
			}
		default:
			{
				return QVariant();
			}
		}

	}


	QVariant LayerObjectsModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
	{
		if( role == Qt::DisplayRole )
		{
			if( section == 0 )
			{
				return QString( tr("Object Id") );
			}
		}

		return QVariant();
	}

	int LayerObjectsModel::rowCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			return 0;
		}

		return m_layer_objects.size();
	}

	int LayerObjectsModel::columnCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		return 1;
	}

	bool LayerObjectsModel::hasChildren( const QModelIndex & parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			return false;
		}

		return !m_layer_objects.empty();
	}


}
	

}
#include "canvaslayersmodel.hpp"


#include "utilcpp/assert.hpp"

#include "aosl/layer.hpp"
#include "aosl/canvas.hpp"

namespace aosd
{
namespace view
{
	CanvasLayersModel::CanvasLayersModel()
	{
	}
	
	CanvasLayersModel::CanvasLayersModel( const aosl::Canvas& canvas )
	{
		update( canvas );
	}


	QVariant CanvasLayersModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
	{
		if( role == Qt::DisplayRole )
		{
			if( section == 0 ) return QString( tr("Layer Id") );
		}

		return QVariant();
	}


	QVariant CanvasLayersModel::data( const QModelIndex& index, int role /*= Qt::DisplayRole */ ) const
	{
		if( !index.isValid() || index.column() > 0 || m_layers.empty() )
			return QVariant();
		
		auto layer = m_layers[ index.row() ];
		UTILCPP_ASSERT_NOT_NULL( layer );

		switch( role )
		{
		case( Qt::DisplayRole ):
			{
				return QString::fromStdString( layer->id() );
			}
		default:
			{
				return QVariant();
			}
		}

		
	}

	void CanvasLayersModel::clear()
	{
		beginResetModel();
		m_layers.clear();
		endResetModel();
	}

	void CanvasLayersModel::update( const aosl::Canvas& canvas )
	{
		clear();

		beginResetModel();
		if( canvas.layers() )
		{
			const auto& layer_list = canvas.layers()->layer();

			std::for_each( layer_list.begin(), layer_list.end(), [&]( const aosl::Layer& layer )
			{
				m_layers.push_back( &layer );
			});
		}

		if( !m_layers.empty() )
		{
			emit dataChanged( createIndex( 0, 0 ), createIndex( m_layers.size() - 1, 0 ) );
		}
		endResetModel();
		
	}

	QModelIndex CanvasLayersModel::index( int row, int column, const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( m_layers.empty() )
			return QModelIndex();

		UTILCPP_ASSERT( !parent.isValid(), "Try to ge the index of child of layer but there is no child!" );

		return createIndex( row, column, (void*)m_layers[row] );
	}

	QModelIndex CanvasLayersModel::parent( const QModelIndex& index ) const
	{
		return QModelIndex();
	}

	Qt::ItemFlags CanvasLayersModel::flags( const QModelIndex& index ) const
	{
		return QAbstractItemModel::flags( index ) | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
	}

	bool CanvasLayersModel::hasChildren( const QModelIndex & parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			return false;
		}

		return !m_layers.empty();
	}

	int CanvasLayersModel::rowCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			return 0;
		}
		return m_layers.size();
	}

	int CanvasLayersModel::columnCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		return 1;
	}



}
}
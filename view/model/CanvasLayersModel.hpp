#ifndef HGUARD_AOSD_VIEW_CANVASLAYERSMODEL_HPP__
#define HGUARD_AOSD_VIEW_CANVASLAYERSMODEL_HPP__
#pragma once

#include <vector>
#include <QAbstractItemModel>

namespace aosl
{
	class Layer;
	class Canvas;
}

namespace aosd
{
namespace view
{

	/** Model representing the Layers and their state in a Canvas.
	**/
	class CanvasLayersModel
		: public QAbstractItemModel
	{
		Q_OBJECT
	public:

		CanvasLayersModel();
		explicit CanvasLayersModel( const aosl::Canvas& canvas );

		QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
		QModelIndex parent( const QModelIndex& index ) const;

		Qt::ItemFlags flags( const QModelIndex& index ) const;
		QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
		QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

		bool hasChildren( const QModelIndex & parent = QModelIndex() ) const;
		int rowCount( const QModelIndex& parent = QModelIndex() ) const;
		int columnCount( const QModelIndex& parent = QModelIndex() ) const;


		void update( const aosl::Canvas& canvas );
		void clear();

		
	private:

		std::vector< const aosl::Layer* > m_layers;

	};

}
}


#endif

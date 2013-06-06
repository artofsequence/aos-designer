#ifndef HGUARD_AOSD_VIEW_CANVASOBJECTSMODEL_HPP__
#define HGUARD_AOSD_VIEW_CANVASOBJECTSMODEL_HPP__
#pragma once

#include <map>
#include <vector>
#include <QAbstractItemModel>

#include <aoslcpp/algorithm/iterator.hpp>

namespace aosl
{
	class Canvas;
	class Object;
}

namespace aosd
{
namespace view
{

	/** Model representing the trees of Objects in a Canvas.
	**/
	class CanvasObjectsModel
		: public QAbstractItemModel
	{
		Q_OBJECT
	public:

		CanvasObjectsModel();
		explicit CanvasObjectsModel( const aosl::Canvas& canvas );
		

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

		std::map< const aosl::Object*, aoslcpp::ObjectTreeNodeInfo > m_object_registry;
		std::vector< const aosl::Object* > m_root_objects;

		aoslcpp::ObjectTreeNodeInfo find_info( const aosl::Object& object ) const;

	};

}
}


#endif

#ifndef HGUARD_AOSD_VIEW_LIBRARYMODEL_HPP__
#define HGUARD_AOSD_VIEW_LIBRARYMODEL_HPP__
#pragma once

#include <vector>
#include <QAbstractItemModel>

#include "core/resources/ResourceRef.hpp"

namespace aosd
{
namespace core
{
	class Library;
	class Resource;
}
namespace view
{
	class LibraryModel
		: public QAbstractItemModel
	{
		Q_OBJECT
	public:

		LibraryModel();

		void update( const core::Library& library );
		void clear();

		QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
		QModelIndex parent( const QModelIndex& index ) const;

		Qt::ItemFlags flags( const QModelIndex& index ) const;
		QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
		QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

		bool hasChildren( const QModelIndex & parent = QModelIndex() ) const;
		int rowCount( const QModelIndex& parent = QModelIndex() ) const;
		int columnCount( const QModelIndex& parent = QModelIndex() ) const;
		
	private:

		

		std::vector< core::ResourceRef > m_resources;

	};

}
}


#endif

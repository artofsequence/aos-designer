#ifndef HGUARD_AOSD_VIEW_LASTCHANGESMODEL_HPP__
#define HGUARD_AOSD_VIEW_LASTCHANGESMODEL_HPP__
#pragma once

#include <vector>
#include <QAbstractItemModel>

namespace aoslcpp
{
	class StoryPath;
}
namespace aosl
{
	class Story;
	class Canvas;
	class Change;
}

namespace aosd
{
namespace view
{
	class LastChangesModel
		: public QAbstractItemModel
	{
		Q_OBJECT
	public:

		LastChangesModel();
		
		QModelIndex index( int row, int column, const QModelIndex& parent = QModelIndex() ) const;
		QModelIndex parent( const QModelIndex& index ) const;

		Qt::ItemFlags flags( const QModelIndex& index ) const;
		QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
		QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;

		bool hasChildren( const QModelIndex & parent = QModelIndex() ) const;
		int rowCount( const QModelIndex& parent = QModelIndex() ) const;
		int columnCount( const QModelIndex& parent = QModelIndex() ) const;


		void update( const aoslcpp::StoryPath& current_path, const aosl::Canvas& canvas, const aosl::Story& story );
		void clear();


	private:
		
		std::vector< const aosl::Change* > m_last_changes;

	};

}
}


#endif

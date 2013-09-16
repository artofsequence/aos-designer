#include "librarymodel.hpp"

#include <algorithm>

#include <aosdesigner/backend/resource.hpp>
#include <aosdesigner/backend/library.hpp>

#include <utilcpp/assert.hpp>


namespace aosd
{
namespace view
{


	LibraryModel::LibraryModel()
	{
		
	}

	void LibraryModel::update( const backend::Library& library )
	{
		clear();

		beginResetModel();
		
		library.for_each_resource( [&]( backend::ResourceRef resource_ref )
		{
			m_resources.push_back( resource_ref );
		});
		
		endResetModel();
	}

	void LibraryModel::clear()
	{
		beginResetModel();
		m_resources.clear();
		endResetModel();
	}

	QModelIndex LibraryModel::index( int row, int column, const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( m_resources.empty() )
			return QModelIndex();

		UTILCPP_ASSERT( !parent.isValid(), "Try to ge the index of child of a resource but it's forbidden!" );

		return createIndex( row, column );
	}

	QModelIndex LibraryModel::parent( const QModelIndex& index ) const
	{
		return QModelIndex();
	}

	Qt::ItemFlags LibraryModel::flags( const QModelIndex& index ) const
	{
		return QAbstractItemModel::flags( index ) | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
	}

	QVariant LibraryModel::data( const QModelIndex& index, int role /*= Qt::DisplayRole */ ) const
	{
		if( !index.isValid() || m_resources.empty() )
			return QVariant();

		auto resource_ref = m_resources[ static_cast<size_t>(index.row()) ];
		UTILCPP_ASSERT_NOT_NULL( resource_ref.resource() );

		switch( role )
		{
		case( Qt::DisplayRole ):
			{
				switch( index.column() )
				{
				case 0: return QString::fromStdString( resource_ref.id() );
				case 1: return QString::fromStdString( resource_ref.resource()->type_name() ); 
				}
			}
		default:
			{
				return QVariant();
			}
		}
	}

	QVariant LibraryModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
	{
		if( role == Qt::DisplayRole )
		{
			switch( section )
			{
			case 0 : return QString( tr("Resource Id") );
			case 1 : return QString( tr("Resource Type") );
			}
		}

		return QVariant();
	}

	bool LibraryModel::hasChildren( const QModelIndex & parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			return false;
		}

		return !m_resources.empty();
	}

	int LibraryModel::rowCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			return 0;
		}

		return m_resources.size();
	}

	int LibraryModel::columnCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		return 2;
	}

}
}
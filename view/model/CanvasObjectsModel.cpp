#include "CanvasObjectsModel.hpp"

#include <algorithm>

#include "utilcpp/Assert.hpp"


#include "aosl/object.hpp"
#include "aosl/canvas.hpp"

namespace aosd
{
namespace view
{
	CanvasObjectsModel::CanvasObjectsModel()
	{
	}
	
	CanvasObjectsModel::CanvasObjectsModel( const aosl::Canvas& canvas )
	{
		update( canvas );
	}

	void CanvasObjectsModel::update( const aosl::Canvas& canvas )
	{
		clear();

		beginResetModel();

		using namespace aoslcpp;
		// go through the object tree and register each object

		std::for_each( objects_iterator_breadth::begin( canvas ), objects_iterator_breadth::end(), [&]( const ObjectTreeNodeInfos& infos )
		{
			m_object_registry.insert( std::make_pair( infos.object(), infos ) );

			if( infos.depth() == 0 )
			{
				m_root_objects.push_back( infos.object() );
			}

		});

		endResetModel();

	}


	void CanvasObjectsModel::clear()
	{
		beginResetModel();
		m_object_registry.clear();
		m_root_objects.clear();
		endResetModel();
	}
	

	QModelIndex CanvasObjectsModel::index( int row, int column, const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( m_root_objects.empty() )
			return QModelIndex();

		if( !parent.isValid() )
		{
			UTILCPP_ASSERT( row < m_root_objects.size(), "Tried to get root object with a wrong index : row = " << row << ", root objects count = " << m_root_objects.size() );
			//if( row < m_root_objects.size() )
				return createIndex( row, 0, (void*)m_root_objects[row] );
			//else
			//	return QModelIndex();
		}

		auto parent_object = static_cast<const aosl::Object*>( parent.internalPointer() );
		
		UTILCPP_ASSERT_NOT_NULL( parent_object );
		UTILCPP_ASSERT_NOT_NULL( parent_object->children() );
		UTILCPP_ASSERT( row < parent_object->children()->object().size(), "Tried to get child object from parent object \""<< parent_object->id() << "\" with a wrong child index : row = " << row << ", root objects count = " << parent_object->children()->object().size() );

		const aosl::Object& child_object = parent_object->children()->object()[ row ];

		return createIndex( row, 0, (void*)&child_object );
	}

	QModelIndex CanvasObjectsModel::parent( const QModelIndex& index ) const
	{
		if( m_root_objects.empty() )
			return QModelIndex();

		if( !index.isValid() )
		{
			return QModelIndex();
		}

		auto object = static_cast< const aosl::Object* >( index.internalPointer() );
		UTILCPP_ASSERT_NOT_NULL( object );

		auto object_infos = find_infos( *object );
		if( object_infos.parent() )
		{
			auto parent_infos = find_infos( *object_infos.parent() );
			return createIndex( parent_infos.idx(), 0, (void*)parent_infos.object() );
		}

		return QModelIndex();
	}

	Qt::ItemFlags CanvasObjectsModel::flags( const QModelIndex& index ) const
	{
		/** auto infos = find( index );
		if( infos )
		{
			return Qt::ItemIsSelectable; // TODO : add flags here if necessary
		}

		return Qt::NoItemFlags;
		*/
		return QAbstractItemModel::flags( index ) | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
	}

	QVariant CanvasObjectsModel::data( const QModelIndex& index, int role /*= Qt::DisplayRole */ ) const
	{
		if( m_root_objects.empty() || !index.isValid() )
			return QVariant();

		auto object = static_cast< const aosl::Object* >( index.internalPointer() );
		UTILCPP_ASSERT_NOT_NULL( object );

		switch( role )
		{
		case( Qt::DisplayRole ):
			{
				// there is no "name" of objects so we use the id as name
				return QString::fromStdString( object->id() );
			}
		case( Qt::CheckStateRole ):
			{
				// display a checked object if it's active, unchecked if it's not
				return object->active() ? Qt::Checked : Qt::Unchecked;
			}
			// TODO : add here other informations possible

		default:
			{
				return QVariant();
			}
		}
	}

	QVariant CanvasObjectsModel::headerData( int section, Qt::Orientation orientation, int role /*= Qt::DisplayRole */ ) const
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

	int CanvasObjectsModel::rowCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			auto parent_object = static_cast<const aosl::Object*>( parent.internalPointer() );
			UTILCPP_ASSERT_NOT_NULL( parent_object );
			if( parent_object->children()  )
			{
				return parent_object->children()->object().size();
			}
			else return 0;
		}
		else return m_root_objects.size();
	}

	int CanvasObjectsModel::columnCount( const QModelIndex& parent /*= QModelIndex() */ ) const
	{
		return 1;
	}

	bool CanvasObjectsModel::hasChildren( const QModelIndex & parent /*= QModelIndex() */ ) const
	{
		if( parent.isValid() )
		{
			auto parent_object = static_cast< const aosl::Object* >( parent.internalPointer() );
			UTILCPP_ASSERT_NOT_NULL( parent_object );

			if( parent_object->children() )
				return !parent_object->children()->object().empty();
			else
				return false;
		}

		return !m_root_objects.empty();
	}

	aoslcpp::ObjectTreeNodeInfos CanvasObjectsModel::find_infos( const aosl::Object& object ) const
	{
		using namespace aoslcpp;

		auto find_it = m_object_registry.find( &object );
		if( find_it != m_object_registry.end() )
		{
			return find_it->second;
		}

		return ObjectTreeNodeInfos();
	}




	

}
}
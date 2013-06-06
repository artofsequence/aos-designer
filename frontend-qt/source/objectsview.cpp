#include "objectsview.hpp"

#include <QStandardItemModel>
#include <QTreeView>

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/editor.hpp>

#include <aoslcpp/algorithm/iterator.hpp>


namespace aosd
{
namespace view
{

	ObjectsView::ObjectsView()
		: m_object_tree_view( new QTreeView() )
		, m_model_binder( *m_object_tree_view )
	{
		setWindowTitle( tr("Objects") );
		setWidget( m_object_tree_view.get() );
		
	}


	ObjectsView::~ObjectsView()
	{

	}


	void ObjectsView::connect_edition( const backend::Editor& editor )
	{
		bool has_model = m_model_binder.load( editor.id() );
		if( !has_model )
		{
			begin_model( editor );
		}
	}

	void ObjectsView::disconnect_edition( const backend::Editor& editor )
	{
		m_model_binder.unload();
	}

	void ObjectsView::begin_editor( const backend::Editor& editor )
	{
		begin_model( editor );
	}

	void ObjectsView::end_editor( const backend::Editor& editor )
	{
		end_model( editor.id() );
	}

	void ObjectsView::begin_model( const backend::Editor& editor )
	{
		m_model_binder.add( std::unique_ptr<QAbstractItemModel>(new CanvasObjectsModel( editor.canvas() )), editor.id() );
		m_model_binder.load( editor.id() );
	}

	void ObjectsView::end_model( const backend::EditorId& edition_id )
	{
		m_model_binder.remove( edition_id );
	}

	



}

}
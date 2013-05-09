#include "objectsview.hpp"

#include <QStandardItemModel>
#include <QTreeView>

#include "core/context.hpp"
#include "core/project.hpp"
#include "core/editionsession.hpp"

#include "aoslcpp/algorithm/iterator.hpp"


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


	void ObjectsView::connect_edition( const core::EditionSession& edition_session )
	{
		bool has_model = m_model_binder.load( edition_session.id() );
		if( !has_model )
		{
			begin_model( edition_session );
		}
	}

	void ObjectsView::disconnect_edition( const core::EditionSession& edition_session )
	{
		m_model_binder.unload();
	}

	void ObjectsView::begin_edition_session( const core::EditionSession& edition_session )
	{
		begin_model( edition_session );
	}

	void ObjectsView::end_edition_session( const core::EditionSession& edition_session )
	{
		end_model( edition_session.id() );
	}

	void ObjectsView::begin_model( const core::EditionSession& edition_session )
	{
		m_model_binder.add( std::unique_ptr<QAbstractItemModel>(new CanvasObjectsModel( edition_session.canvas() )), edition_session.id() );
		m_model_binder.load( edition_session.id() );
	}

	void ObjectsView::end_model( const core::EditionSessionId& edition_id )
	{
		m_model_binder.remove( edition_id );
	}

	



}

}
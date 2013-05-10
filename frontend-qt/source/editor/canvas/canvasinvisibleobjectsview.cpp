#include "canvasinvisibleobjectsview.hpp"

#include <QGraphicsScene>

#include <aosdesigner/backend/library.hpp>
#include <aosl/canvas.hpp>

namespace aosd
{
namespace view
{

	CanvasInvisibleObjectsView::CanvasInvisibleObjectsView()
		: m_scene( new QGraphicsScene )
	{
		setFixedHeight( 80 );
		setBackgroundBrush( QBrush( QColor( Qt::darkGreen ) ) );


		setScene( m_scene.get() );
	}

	CanvasInvisibleObjectsView::~CanvasInvisibleObjectsView()
	{

	}

	void CanvasInvisibleObjectsView::clear()
	{

	}

	void CanvasInvisibleObjectsView::update( const aosl::Canvas& canvas, const backend::Library& sequence_library, const backend::Library& project_library   )
	{

	}

}
}
#include "canvasview.hpp"

#include "canvasgraphicsview.hpp"
#include "canvasinvisibleobjectsview.hpp"

namespace aosd
{
namespace view
{

	CanvasView::CanvasView()
		: m_graphic_view( new CanvasGraphicsView )
		, m_others_view( new CanvasInvisibleObjectsView )
	{
		setOrientation( Qt::Vertical );
		addWidget( m_graphic_view.get() );
		addWidget( m_others_view.get() );

	}

	CanvasView::~CanvasView()
	{

	}

	void CanvasView::clear()
	{

	}

	void CanvasView::update( const aosl::Canvas& canvas, const backend::Library& sequence_library, const backend::Library& project_library )
	{
		m_graphic_view->update( canvas, sequence_library, project_library );
		m_others_view->update( canvas, sequence_library, project_library );
	}

}
}
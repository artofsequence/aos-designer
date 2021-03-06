#ifndef HGUARD_AOSD_VIEW_CANVASINVISIBLECONTENTVIEW_HPP__
#define HGUARD_AOSD_VIEW_CANVASINVISIBLECONTENTVIEW_HPP__
#pragma once

#include <memory>
#include <QGraphicsView>


class QGraphicsScene;


namespace aosl
{
	class Canvas;
}

namespace aosd
{
namespace backend
{
	class Library;
}
namespace view
{
	/** Display non-graphics objects activated in a canvas.
	*/
	class CanvasInvisibleObjectsView
		: public QGraphicsView
	{
		Q_OBJECT
	public:
	
		CanvasInvisibleObjectsView();
		~CanvasInvisibleObjectsView();

	public slots:

		void clear();
		void update( const aosl::Canvas& canvas, const backend::Library& sequence_library, const backend::Library& project_library   );

	private:

		std::unique_ptr< QGraphicsScene > m_scene;
		
	};

}
}


#endif
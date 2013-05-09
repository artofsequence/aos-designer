#ifndef HGUARD_AOSD_VIEW_CANVASGRAPHICSVIEW_HPP__
#define HGUARD_AOSD_VIEW_CANVASGRAPHICSVIEW_HPP__
#pragma once

#include <memory>
#include <QGraphicsView>

class QGraphicsScene;


namespace aosl
{
	class Canvas;
	class Object;
}


namespace aosd
{
namespace backend
{
	class Library;
}
namespace view
{

	/** Display the graphics view of a canvas.
		
	*/
	class CanvasGraphicsView
		: public QGraphicsView
	{
		Q_OBJECT
	public:

		CanvasGraphicsView();
		~CanvasGraphicsView();

	public slots:

		void clear();
		void update( const aosl::Canvas& canvas, const backend::Library& sequence_library, const backend::Library& project_library  );

	private:

		std::unique_ptr<QGraphicsScene> m_scene;

		void add_graphic_object( const aosl::Object& object );
		
	};


}
}


#endif
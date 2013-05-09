#ifndef HGUARD_AOSD_VIEW_CANVASVIEW_HPP__
#define HGUARD_AOSD_VIEW_CANVASVIEW_HPP__
#pragma once

#include <memory>
#include <QSplitter>

namespace aosl
{
	class Canvas;
	
}

namespace aosd 
{
namespace core
{
	class Library;
}
namespace view
{
	class CanvasGraphicsView;
	class CanvasInvisibleObjectsView;

	/** Display a graphic representation of the canvas of a Sequence 
		at a specific stage of a story being played.
		It allows to edit and move the content of the Canvas for this stage.
	**/
	class CanvasView
		: public QSplitter
	{
		Q_OBJECT
	public:
		
		CanvasView();
		~CanvasView();

	public slots:

		void clear();
		void update( const aosl::Canvas& canvas, const core::Library& sequence_library, const core::Library& project_library  );

	private:

		std::unique_ptr<CanvasGraphicsView> m_graphic_view;
		std::unique_ptr<CanvasInvisibleObjectsView> m_others_view;



	};


}
}

#endif

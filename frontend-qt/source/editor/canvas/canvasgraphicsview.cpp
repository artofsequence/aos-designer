#include "canvasgraphicsview.hpp"

#include <QGraphicsScene>

#include "utilcpp/log.hpp"

#include "aosl/object.hpp"
#include "aosl/canvas.hpp"
#include "aoslcpp/algorithm/for_each.hpp"

#include "core/library.hpp"

namespace aosd
{
namespace view
{
	
	CanvasGraphicsView::CanvasGraphicsView()
		: m_scene( new QGraphicsScene )
	{

		setBackgroundBrush( QBrush( QColor( Qt::black ) ) );
		setScene( m_scene.get() );
	}

	CanvasGraphicsView::~CanvasGraphicsView()
	{

	}

	void CanvasGraphicsView::clear()
	{

	}

	void CanvasGraphicsView::update( const aosl::Canvas& canvas, const core::Library& sequence_library, const core::Library& project_library   )
	{
		aoslcpp::for_each_object_depth( canvas, [&]( const aosl::Object& object )
		{
			if( object.resource() )
			{
				auto resource_id = aosl::Resource_id(*object.resource());
				core::ResourcePtr resource = sequence_library.find( resource_id );
				if( !resource )
				{
					resource = project_library.find( resource_id );
					if( !resource )
					{
						UTILCPP_LOG_ERROR << "Resource id \"" << *object.resource() << "\" for object \"" << object.id() << "\" not found in sequence and project libraries.";
					}
				}
			}
			
		});


	}

	void CanvasGraphicsView::add_graphic_object( const aosl::Object& object )
	{

	}

}
}
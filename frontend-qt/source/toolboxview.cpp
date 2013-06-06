#include "toolboxview.hpp"

namespace aosd
{
namespace view
{


	ToolboxView::ToolboxView()
	{
		setWindowTitle( tr("Toolbox") );
		setWidget( new QToolBox() );
	}

	void ToolboxView::connect_edition( const backend::Editor& editor )
	{

	}

	void ToolboxView::disconnect_edition( const backend::Editor& editor )
	{

	}

}
}
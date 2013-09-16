#ifndef HGUARD_AOSD_VIEW_TOOLBOXVIEW_HPP__
#define HGUARD_AOSD_VIEW_TOOLBOXVIEW_HPP__
#pragma once

#include <QToolBox>
#include "editiontoolview.hpp"

namespace aosd
{
namespace view
{
	/** Display tools for edition.
	**/
	class ToolboxView
		: public EditionToolView
	{
		Q_OBJECT
	public:
		
		ToolboxView();

	private:

		void begin_editor( const backend::Editor& editor ){}
		void end_editor( const backend::Editor& editor ){}
		void connect_edition( const backend::Editor& editor );
		void disconnect_edition( const backend::Editor& editor );

	};


}
}


#endif

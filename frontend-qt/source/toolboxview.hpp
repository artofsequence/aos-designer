#ifndef HGUARD_AOSD_VIEW_TOOLBOXVIEW_HPP__
#define HGUARD_AOSD_VIEW_TOOLBOXVIEW_HPP__
#pragma once

#include <QToolBox>
#include "view/editiontoolview.hpp"

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

		void begin_edition_session( const core::EditionSession& edition_session ){}
		void end_edition_session( const core::EditionSession& edition_session ){}
		void connect_edition( const core::EditionSession& edition_session );
		void disconnect_edition( const core::EditionSession& edition_session );

	};


}
}


#endif

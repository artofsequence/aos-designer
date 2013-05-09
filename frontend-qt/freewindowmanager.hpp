#ifndef HGUARD_AOSD_VIEW_FREEWINDOWMANAGER_HPP__
#define HGUARD_AOSD_VIEW_FREEWINDOWMANAGER_HPP__
#pragma once

#include <map>
#include <memory>

#include "view/freewindow.hpp"

class QWidget;
class QMdiArea;

namespace aosd
{
namespace view
{

	/** Manage a set of FreeWindow that are used in an MdiArea.
	**/
	class FreeWindowManager
	{
	public:

		FreeWindowManager( QMdiArea& internal_area );
		~FreeWindowManager();

		FreeWindow& add_window( QWidget& widget );
		void remove_window( QWidget& widget );
		
		FreeWindow* find_window( QWidget& widget );

		void clear();

	private:

		std::map< QWidget*, std::unique_ptr<FreeWindow> > m_windows_registry;

		QMdiArea& m_internal_area;

		

	};

}
}


#endif
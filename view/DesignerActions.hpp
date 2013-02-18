#ifndef HGUARD_AOSD_VIEW_DESIGNERACTIONS_HPP__
#define HGUARD_AOSD_VIEW_DESIGNERACTIONS_HPP__
#pragma once

#include <QAction>

namespace aosd
{
namespace view
{
	
	/** Provide actions for manipulating the Designer(the application).
	*/
	class DesignerActions
	{
	public:

		

		DesignerActions();

		/** Setup a full main menu. 
		**/
		void setup_menubar( QMenuBar& menubar );

		

	private:

		QAction m_quit;
		QAction m_new_project;
		QAction m_open_project;
		QAction m_close_project;

		QAction m_new_sequence;
		QAction m_save_project;
		QAction m_restore_project;

		QAction m_new_edition;


	};

}
}


#endif
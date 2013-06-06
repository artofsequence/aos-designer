#ifndef HGUARD_AOSD_VIEW_EDITIONTOOLVIEW_HPP__
#define HGUARD_AOSD_VIEW_EDITIONTOOLVIEW_HPP__
#pragma once

#include <QDockWidget>

namespace aosd
{

namespace backend
{
	class Project;
	class Editor;
}

namespace view
{
	class EditionToolView
		: public QDockWidget
	{
		Q_OBJECT
	protected:
		
		EditionToolView();
		virtual ~EditionToolView();

		void activate() { change_state( true ); }
		void deactivate()  { change_state( false ); }


		virtual void begin_editor( const backend::Editor& editor ) = 0;
		virtual void end_editor( const backend::Editor& editor ) = 0;

		virtual void connect_edition( const backend::Editor& editor ) = 0;
		virtual void disconnect_edition( const backend::Editor& editor ) = 0;

		virtual void connect_project( const backend::Project& project ) {}
		virtual void disconnect_project( const backend::Project& project ) {}

	
	private slots:

		void react_project_open( const backend::Project& );
		void react_project_closed( const backend::Project& );

		void react_edition_begin();
		void react_edition_end();

		void react_editor_begin( const backend::Editor& editor );
		void react_editor_end( const backend::Editor& editor );

		void react_edition_selected( const backend::Editor& editor );
		void react_edition_deselected( const backend::Editor& editor );
		
	private:
		
		void change_state( bool is_active );

	};

}
}


#endif

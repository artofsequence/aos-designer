#ifndef HGUARD_AOSD_VIEW_EDITIONTOOLVIEW_HPP__
#define HGUARD_AOSD_VIEW_EDITIONTOOLVIEW_HPP__
#pragma once

#include <QDockWidget>

namespace aosd
{

namespace backend
{
	class Project;
	class EditionSession;
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


		virtual void begin_edition_session( const backend::EditionSession& edition_session ) = 0;
		virtual void end_edition_session( const backend::EditionSession& edition_session ) = 0;

		virtual void connect_edition( const backend::EditionSession& edition_session ) = 0;
		virtual void disconnect_edition( const backend::EditionSession& edition_session ) = 0;

		virtual void connect_project( const backend::Project& project ) {}
		virtual void disconnect_project( const backend::Project& project ) {}

	
	private slots:

		void react_project_open( const backend::Project& );
		void react_project_closed( const backend::Project& );

		void react_edition_begin();
		void react_edition_end();

		void react_edition_session_begin( const backend::EditionSession& edition_session );
		void react_edition_session_end( const backend::EditionSession& edition_session );

		void react_edition_selected( const backend::EditionSession& edition_session );
		void react_edition_deselected( const backend::EditionSession& edition_session );
		
	private:
		
		void change_state( bool is_active );

	};

}
}


#endif

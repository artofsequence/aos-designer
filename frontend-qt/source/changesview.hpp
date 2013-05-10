#ifndef HGUARD_AOSD_VIEW_CHANGESVIEW_HPP__
#define HGUARD_AOSD_VIEW_CHANGESVIEW_HPP__
#pragma once

#include <memory>

#include <aosdesigner/backend/editionsessionid.hpp>

#include "editiontoolview.hpp"
#include "model/modelviewbinder.hpp"


class QTreeView;

namespace aosd
{
namespace view
{
	/** Display lists of changes between the current story stage and the previous one.
	**/
	class ChangesView
		: public EditionToolView
	{
		Q_OBJECT
	public:

		ChangesView();
		~ChangesView();
		
	private:

		std::unique_ptr< QTreeView > m_last_changes_view;
		ModelViewBinder<backend::EditionSessionId> m_model_view_binder;

		void begin_edition_session( const backend::EditionSession& edition_session );
		void end_edition_session( const backend::EditionSession& edition_session );
		void connect_edition( const backend::EditionSession& edition_session );
		void disconnect_edition( const backend::EditionSession& edition_session );

		void update_last_changes( const backend::EditionSession& edition_session );
		void begin_model( const backend::EditionSession& edition_session );
		void end_model( const backend::EditionSession& edition_session );
	};


}
}


#endif

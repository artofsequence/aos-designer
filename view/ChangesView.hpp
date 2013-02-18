#ifndef HGUARD_AOSD_VIEW_CHANGESVIEW_HPP__
#define HGUARD_AOSD_VIEW_CHANGESVIEW_HPP__
#pragma once

#include <memory>
#include "view/EditionToolView.hpp"
#include "view/model/ModelViewBinder.hpp"

#include "core/EditionSessionId.hpp"

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
		ModelViewBinder<core::EditionSessionId> m_model_view_binder;

		void begin_edition_session( const core::EditionSession& edition_session );
		void end_edition_session( const core::EditionSession& edition_session );
		void connect_edition( const core::EditionSession& edition_session );
		void disconnect_edition( const core::EditionSession& edition_session );

		void update_last_changes( const core::EditionSession& edition_session );
		void begin_model( const core::EditionSession& edition_session );
		void end_model( const core::EditionSession& edition_session );
	};


}
}


#endif

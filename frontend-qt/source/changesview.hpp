#ifndef HGUARD_AOSD_VIEW_CHANGESVIEW_HPP__
#define HGUARD_AOSD_VIEW_CHANGESVIEW_HPP__
#pragma once

#include <memory>

#include <aosdesigner/backend/id.hpp>

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
		ModelViewBinder<backend::EditorId> m_model_view_binder;

		void begin_editor( const backend::Editor& editor );
		void end_editor( const backend::Editor& editor );
		void connect_edition( const backend::Editor& editor );
		void disconnect_edition( const backend::Editor& editor );

		void update_last_changes( const backend::Editor& editor );
		void begin_model( const backend::Editor& editor );
		void end_model( const backend::Editor& editor );
	};


}
}


#endif

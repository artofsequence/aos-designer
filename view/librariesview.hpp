#ifndef HGUARD_AOSD_VIEW_LIBRARIESVIEW_HPP__
#define HGUARD_AOSD_VIEW_LIBRARIESVIEW_HPP__
#pragma once

#include <memory>
#include "view/editiontoolview.hpp"
#include "view/model/modelviewbinder.hpp"
#include "core/sequenceid.hpp"

class QTreeView;
class QSplitter;

namespace aosd
{

namespace core
{
	class Sequence;
}
namespace view
{
	class LibraryModel;
	
	/** Display lists of resources for each libraries used in the current sequence.
		Allow editing, adding and removing resources from libraries.
	**/
	class LibrariesView
		: public EditionToolView
	{

		Q_OBJECT
	public:
		
		LibrariesView();

	private:

		std::unique_ptr<QSplitter> m_splitter;
		std::unique_ptr<QTreeView> m_sequence_library_view;
		std::unique_ptr<QTreeView> m_project_library_view;

		std::unique_ptr<LibraryModel> m_project_library_model;
		ModelViewBinder<core::SequenceId> m_sequence_model_view_binder;
		

		void begin_edition_session( const core::EditionSession& edition_session );
		void end_edition_session( const core::EditionSession& edition_session );
		void connect_edition( const core::EditionSession& edition_session );
		void disconnect_edition( const core::EditionSession& edition_session );
		void connect_project( const core::Project& project );
		void disconnect_project( const core::Project& project );

		void add_sequence_library( const core::Sequence& sequence );
		

	};


}
}

#endif

#ifndef HGUARD_AOSD_VIEW_LIBRARIESVIEW_HPP__
#define HGUARD_AOSD_VIEW_LIBRARIESVIEW_HPP__
#pragma once

#include <memory>
#include "editiontoolview.hpp"
#include "model/modelviewbinder.hpp"
#include <aosdesigner/backend/id.hpp>

class QTreeView;
class QSplitter;

namespace aosd
{

namespace backend
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
		ModelViewBinder<backend::SequenceId> m_sequence_model_view_binder;
		

		void begin_editor( const backend::Editor& editor );
		void end_editor( const backend::Editor& editor );
		void connect_edition( const backend::Editor& editor );
		void disconnect_edition( const backend::Editor& editor );
		void connect_project( const backend::Project& project );
		void disconnect_project( const backend::Project& project );

		void add_sequence_library( const backend::Sequence& sequence );
		

	};


}
}

#endif

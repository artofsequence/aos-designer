#ifndef HGUARD_AOSD_VIEW_OBJECTSVIEW_HPP__
#define HGUARD_AOSD_VIEW_OBJECTSVIEW_HPP__
#pragma once

#include <map>
#include <memory>
#include <aosdesigner/backend/id.hpp>
#include "editiontoolview.hpp"
#include "model/modelviewbinder.hpp"
#include "model/canvasobjectsmodel.hpp"

class QTreeView;

namespace aosd
{
namespace backend 
{ 
	class Editor; 
	class Project;
}

namespace view
{
	/** Display objects in the canvas, separated as active and inactive, at the current stage of the story.
		Allows editing, adding and removing objects.
	**/
	class ObjectsView
		: public EditionToolView
	{
		Q_OBJECT
	public:
		
		ObjectsView();
		~ObjectsView();

	private:

		std::unique_ptr<QTreeView> m_object_tree_view;
		ModelViewBinder<backend::EditorId> m_model_binder;
		
		void begin_editor( const backend::Editor& editor );
		void end_editor( const backend::Editor& editor );
		void connect_edition( const backend::Editor& editor );
		void disconnect_edition( const backend::Editor& editor );

		void begin_model( const backend::Editor& editor );
		void end_model( const backend::EditorId& edition_id );

	};


}
}

#endif

#ifndef HGUARD_AOSD_BACKEND_EDITOREVENTS_HPP__
#define HGUARD_AOSD_BACKEND_EDITOREVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/editorinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct EditorOpen				///< An Editor have been opened and is ready to edit the associated Sequence.
	{
		ProjectId	project_id;		///< Project in which the Editor have been opened.
		EditorInfo	editor_info;	///< Info of the open Editor.
	};

	struct EditorClosed				///< An open Editor have been closed and is not available anymore for edition.
	{
		ProjectId	project_id;		///< Project in which the Editor was open.
		EditorId	editor_id;		///< Id of the closed Editor.
	};


}}}

#endif

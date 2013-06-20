#ifndef HGUARD_AOSD_BACKEND_EDITOREVENTS_HPP__
#define HGUARD_AOSD_BACKEND_EDITOREVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/editorinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct EditorOpen
	{
		EditorInfo editor_info;
	};

	struct EditorClosed
	{
		EditorId editor_id;
	};


}}}

#endif

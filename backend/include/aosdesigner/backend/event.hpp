#ifndef HGUARD_AOSD_BACKEND_EVENT_HPP__
#define HGUARD_AOSD_BACKEND_EVENT_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/projectinfo.hpp>
#include <aosdesigner/backend/sequenceinfo.hpp>
#include <aosdesigner/backend/editorinfo.hpp>
#include <aosdesigner/backend/libraryinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct ProjectOpen
	{
		ProjectInfo project_info;
	};

	struct ProjectClosed 
	{
		ProjectId project_id;
	};

	struct LibraryLoaded
	{
		LibraryInfo library_info;
	};

	struct LibraryUnloaded
	{
		LibraryId library_id;
	};
	
	struct SequenceAdded
	{
		SequenceInfo sequence_info;
	};

	struct SequenceRemoved 
	{
		ProjectId project_id;
		SequenceId sequence_id; 
	};

	struct SequenceLoaded
	{
		SequenceInfo sequence_info;
	};

	struct SequenceUnloaded
	{
		SequenceId sequence_id;
	};
	
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

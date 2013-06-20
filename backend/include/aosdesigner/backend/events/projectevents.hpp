#ifndef HGUARD_AOSD_BACKEND_PROJECTEVENTS_HPP__
#define HGUARD_AOSD_BACKEND_PROJECTEVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/projectinfo.hpp>
#include <aosdesigner/backend/info/sequenceinfo.hpp>
#include <aosdesigner/backend/info/libraryinfo.hpp>

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

	struct SequenceAdded
	{
		SequenceInfo sequence_info;
	};

	struct SequenceRemoved 
	{
		ProjectId project_id;
		SequenceId sequence_id; 
	};

	struct LibraryAdded
	{
		LibraryInfo library_info;
	};

	struct LibraryRemoved
	{
		ProjectId project_id;
		LibraryId library_id;
	};

}}}

#endif

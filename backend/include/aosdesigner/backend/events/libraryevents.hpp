#ifndef HGUARD_AOSD_BACKEND_LIBRARYEVENTS_HPP__
#define HGUARD_AOSD_BACKEND_LIBRARYEVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/libraryinfo.hpp>

namespace aosd {
namespace backend {
namespace event {

	struct LibraryLoaded
	{
		LibraryInfo library_info;
	};

	struct LibraryUnloaded
	{
		LibraryId library_id;
	};


}}}

#endif

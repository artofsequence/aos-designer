#ifndef HGUARD_AOSD_BACKEND_LIBRARYEVENTS_HPP__
#define HGUARD_AOSD_BACKEND_LIBRARYEVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/libraryinfo.hpp>

namespace aosd {
namespace backend {
namespace event {

	struct LibraryLoaded				///< A Library data have been loaded and is ready for edition.
	{
		LibraryInfo library_info;		///< Information of the loaded Library.
	};

	struct LibraryUnloaded				///< A loaded Library data have been unloaded and is not available anymore for edition.
	{
		LibraryId library_id;			///< Id of the unloaded Library.
	};


}}}

#endif

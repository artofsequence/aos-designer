#ifndef HGUARD_AOSD_BACKEND_SEQUENCEEVENTS_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCEEVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/sequenceinfo.hpp>
#include <aosdesigner/backend/info/libraryinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct SequenceLoaded				///< A Sequence have been loaded and is ready for edition.
	{
		SequenceInfo	sequence_info;	///< Information of the loaded Sequence.
	};

	struct SequenceUnloaded				///< A loaded Sequence have been unloaded and isn't available anymore.
	{
		SequenceId		sequence_id;	///< Id of the unloaded Sequence.
	};
	
	struct SequenceLibraryAdded			///< An external Library have been added into a Sequence.
	{
		SequenceId		sequence_id;	///< Id of the Sequence in which the external Library have been added.
		LibraryInfo		library_info;	///< Information of the added external library.
	};

	struct SequenceLibraryRemoved		///< An external Library have been removed from a Sequence.
	{
		SequenceId		sequence_id;	///< Id of the Sequence from which the external Library have been removed.
		LibraryId		library_id;		///< Id of the removed external Library.
	};

}}}

#endif

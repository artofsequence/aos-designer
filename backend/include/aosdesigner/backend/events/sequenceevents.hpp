#ifndef HGUARD_AOSD_BACKEND_SEQUENCEEVENTS_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCEEVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/sequenceinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct SequenceLoaded
	{
		SequenceInfo sequence_info;
	};

	struct SequenceUnloaded
	{
		SequenceId sequence_id;
	};
	

}}}

#endif

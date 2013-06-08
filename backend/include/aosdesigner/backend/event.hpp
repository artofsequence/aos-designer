#ifndef HGUARD_AOSD_BACKEND_EVENT_HPP__
#define HGUARD_AOSD_BACKEND_EVENT_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/projectinfo.hpp>
#include <aosdesigner/backend/sequenceinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct ProjectOpen : ProjectInfoEx	{};
	struct ProjectClosed { ProjectId id; };
							
	struct SequenceAdded : SequenceInfo	{  };
	struct SequenceRemoved	{};
							
	struct EditorBegin		{};
	struct EditorEnd		{};

}}}

#endif

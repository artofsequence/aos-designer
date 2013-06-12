#ifndef HGUARD_AOSD_BACKEND_SEQUENCEINFO_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCEINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/uri.hpp>

namespace aosd {
namespace backend {
	
	struct SequenceInfo
	{
		SequenceId		id;
		ProjectId		project_id;
		std::string		name;
	};
	
	inline bool is_valid( const SequenceInfo& info )
	{
		return is_valid( info.id )
			&& is_valid( info.project_id )
			&& !info.name.empty()
			;
	}

}}


#endif

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
		std::string		name;
		URI				aosl_location;
	};
	
	inline bool is_valid( const SequenceInfo& info )
	{
		return is_valid( info.id )
			&& !info.name.empty()
			;
	}

}}


#endif

#ifndef HGUARD_AOSD_BACKEND_SEQUENCEINFO_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCEINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/uri.hpp>

namespace aosd
{
namespace backend
{
	
	struct SequenceInfo
	{
		SequenceInfo() 
			: canvas_width( 0.0 )
			, canvas_height( 0.0 ) 
			, canvas_depth( 0.0 )
		{}

		SequenceId id;
		ProjectId project_id;
		URI location;
		std::string name;
		
		double canvas_width; // = 0.0;
		double canvas_height; // = 0.0;
		double canvas_depth; // = 0.0;

		bool is_valid() const
		{
			return id.is_valid()
				&& !location.empty()
				&& !name.empty()
				&& canvas_height >= 0.0
				&& canvas_width >= 0.0
				;
		}
	};
	
	inline bool is_valid( const SequenceInfo& info )
	{
		return info.is_valid();
	}

}
}


#endif

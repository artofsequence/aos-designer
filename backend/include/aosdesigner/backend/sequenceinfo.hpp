#ifndef HGUARD_AOSD_BACKEND_SEQUENCEINFO_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCEINFO_HPP__
#pragma once

#include <string>
#include <boost/filesystem/path.hpp>

namespace aosd
{
namespace backend
{
	
	struct SequenceInfo
	{
		SequenceInfo() : canvas_width( 0.0 ), canvas_height( 0.0 ), is_edition_requested(false) {}

		boost::filesystem::path location;
		std::string name;
		double canvas_width;
		double canvas_height;
		bool is_edition_requested;

	};

	inline bool is_valid( const SequenceInfo& info )
	{
		return !(	info.location.empty()
				||	info.name.empty()
				||	info.canvas_height <= 0.0
				||  info.canvas_width <= 0.0
			);
	}

}
}


#endif

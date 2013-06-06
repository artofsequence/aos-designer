#ifndef HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#define HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#pragma once

#include <string>
#include <boost/filesystem/path.hpp>


namespace aosd
{
namespace backend
{
	/** Basic information about a project.
	*/
	struct ProjectInfo
	{
		boost::filesystem::path location;
		std::string name;
		
	};

	inline bool is_valid( const ProjectInfo& info )
	{
		return !( info.location.empty() || info.name.empty() );
	}

}
}


#endif

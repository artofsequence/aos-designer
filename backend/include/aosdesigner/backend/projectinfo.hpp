#ifndef HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#define HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/uri.hpp>


namespace aosd
{
namespace backend
{
	/** Basic information about a project.
	*/
	struct ProjectInfo
	{
		ProjectId id;
		std::string name;
		URI location;

		bool is_valid() const
		{
			return id.is_valid()
				&& !location.empty()
				&& !name.empty();
		}
	};

	struct ProjectInfoEx
		: ProjectInfo
	{
		std::vector<SequenceId> sequence_list;
		std::vector<EditorId> editor_list;
	};

	inline bool is_valid( const ProjectInfo& info )
	{
		return info.is_valid();
	}

}
}


#endif

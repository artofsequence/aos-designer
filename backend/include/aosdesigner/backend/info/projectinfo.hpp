#ifndef HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#define HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#pragma once

#include <string>
#include <vector>
#include <aosdesigner/backend/id.hpp>


namespace aosd {
namespace backend {

	struct ProjectInfo
	{
		ProjectId				id;
		std::string				name;

		std::vector<LibraryId>	library_list;
		std::vector<SequenceId> sequence_list;
		std::vector<EditorId>	editor_list;

	};
	
	inline bool is_valid( const ProjectInfo& info )
	{
		return is_valid( info.id )
			&& !info.name.empty();
	}

}}


#endif

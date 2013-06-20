#ifndef HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#define HGUARD_AOSD_BACKEND_PROJECTINFO_HPP__
#pragma once

#include <string>
#include <vector>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/editorinfo.hpp>
#include <aosdesigner/backend/info/libraryinfo.hpp>
#include <aosdesigner/backend/info/sequenceinfo.hpp>

namespace aosd {
namespace backend {

	struct ProjectInfo
	{
		ProjectId				id;
		std::string				name;

		std::vector<LibraryInfo>  library_list;
		std::vector<SequenceInfo> sequence_list;
		std::vector<EditorInfo>	  editor_list;

	};
	
	inline bool is_valid( const ProjectInfo& info )
	{
		return is_valid( info.id )
			&& !info.name.empty();
	}

}}


#endif

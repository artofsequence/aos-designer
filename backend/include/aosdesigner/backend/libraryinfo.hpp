#ifndef HGUARD_AOSD_BACKEND_LIBRARYINFO_HPP__
#define HGUARD_AOSD_BACKEND_LIBRARYINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/uri.hpp>

namespace aosd {
namespace backend {

	struct LibraryInfo
	{
		LibraryId		id;
		std::string		name;
		URI				location;
		ProjectId		project_id;
		SequenceId		sequence_id;
		
		bool is_shared() const { return !is_valid( sequence_id ); }
	};

	inline bool is_valid( const LibraryInfo& info )
	{
		return is_valid( info.id )
			&& is_valid( info.project_id )
			&& !info.name.empty()
			&& !info.location.empty()
			;
	}

}}


#endif

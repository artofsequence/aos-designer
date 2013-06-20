#ifndef HGUARD_AOSD_BACKEND_LIBRARYINFO_HPP__
#define HGUARD_AOSD_BACKEND_LIBRARYINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>

namespace aosd {
namespace backend {

	struct LibraryInfo
	{
		LibraryId		id;
		std::string		name;
	};

	inline bool is_valid( const LibraryInfo& info )
	{
		return is_valid( info.id )
			&& !info.name.empty()
			;
	}

}}


#endif

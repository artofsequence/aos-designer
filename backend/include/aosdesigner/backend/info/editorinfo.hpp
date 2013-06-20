#ifndef HGUARD_AOSD_BACKEND_EDITORINFO_HPP__
#define HGUARD_AOSD_BACKEND_EDITORINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>

namespace aosd {
namespace backend {

	struct EditorInfo
	{
		EditorId		id;
		SequenceId		sequence_id;
	};

	inline bool is_valid( const EditorInfo& info )
	{
		return is_valid( info.id )
			&& is_valid( info.sequence_id )
			;
	}

}}


#endif

#ifndef HGUARD_AOSD_BACKEND_EDITORINFO_HPP__
#define HGUARD_AOSD_BACKEND_EDITORINFO_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>

namespace aosd {
namespace backend {

	struct EditorInfo
	{
		std::string name;
		SequenceId sequence_id;
		
		bool is_valid() const 
		{
			return sequence_id.is_valid()
				&& !name.empty()
				;
		}
		
	};

	inline bool is_valid( const EditorInfo& info )
	{
		return info.is_valid();
	}

}}


#endif

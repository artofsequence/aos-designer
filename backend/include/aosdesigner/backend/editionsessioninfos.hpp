#ifndef HGUARD_AOSD_BACKEND_EDITIONSESSIONINFOS_HPP__
#define HGUARD_AOSD_BACKEND_EDITIONSESSIONINFOS_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/id.hpp>

namespace aosd
{
namespace backend
{
	struct EditionSessionInfos
	{
		std::string name;
		SequenceId sequence_id;
	};

	inline bool is_valid( const EditionSessionInfos& infos )
	{
		return is_valid( infos.sequence_id )
			&& !infos.name.empty()
			;
	}

}
}


#endif

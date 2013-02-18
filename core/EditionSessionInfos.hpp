#ifndef HGUARD_AOSD_CORE_EDITIONSESSIONINFOS_HPP__
#define HGUARD_AOSD_CORE_EDITIONSESSIONINFOS_HPP__
#pragma once

#include <string>
#include "core/SequenceId.hpp"

namespace aosd
{
namespace core
{
	struct EditionSessionInfos
	{
		std::string name;
		SequenceId sequence_id;
	};

	inline bool is_valid( const EditionSessionInfos& infos )
	{
		return !(	infos.sequence_id.empty()
			||	infos.name.empty()
			);
	}

}
}


#endif

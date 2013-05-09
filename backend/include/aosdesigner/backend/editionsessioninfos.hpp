#ifndef HGUARD_AOSD_BACKEND_EDITIONSESSIONINFOS_HPP__
#define HGUARD_AOSD_BACKEND_EDITIONSESSIONINFOS_HPP__
#pragma once

#include <string>
#include <aosdesigner/backend/sequenceid.hpp>

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
		return !(	infos.sequence_id.empty()
			||	infos.name.empty()
			);
	}

}
}


#endif

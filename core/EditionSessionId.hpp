#ifndef HGUARD_AOSD_CORE_EDITIONSESSIONID_HPP__
#define HGUARD_AOSD_CORE_EDITIONSESSIONID_HPP__
#pragma once

#include <string>

namespace aosd
{
namespace core
{
	typedef std::string EditionSessionId;

	extern const EditionSessionId EditionSessionId_INVALID;

	bool is_valid( const EditionSessionId& session_id );

}
}


#endif

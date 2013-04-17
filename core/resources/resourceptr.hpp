#ifndef HGUARD_AOSD_CORE_RESOURCEPTR_H__
#define HGUARD_AOSD_CORE_RESOURCEPTR_H__
#pragma once

#include <memory>

namespace aosd
{
namespace core
{
	class Resource;

	typedef std::shared_ptr< Resource > ResourcePtr;

}
}


#endif

#ifndef HGUARD_AOSD_BACKEND_RESOURCEPTR_H__
#define HGUARD_AOSD_BACKEND_RESOURCEPTR_H__
#pragma once

#include <memory>

namespace aosd
{
namespace backend
{
	class Resource;

	typedef std::shared_ptr< Resource > ResourcePtr;

}
}


#endif

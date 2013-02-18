#ifndef HGUARD_AOSD_CORE_RESOURCEFACTORY_HPP__
#define HGUARD_AOSD_CORE_RESOURCEFACTORY_HPP__
#pragma once

#include "ResourcePtr.hpp"
#include "ResourceInfo.hpp"

namespace aosd
{
namespace core
{

	ResourcePtr create_resource( const ResourceInfo& resource_info );
	
}
}


#endif

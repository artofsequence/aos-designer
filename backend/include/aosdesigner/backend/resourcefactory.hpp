#ifndef HGUARD_AOSD_BACKEND_RESOURCEFACTORY_HPP__
#define HGUARD_AOSD_BACKEND_RESOURCEFACTORY_HPP__
#pragma once

#include <aosdesigner/backend/resourceptr.hpp>
#include <aosdesigner/backend/resourceinfo.hpp>

namespace aosd
{
namespace backend
{

	ResourcePtr create_resource( const ResourceInfo& resource_info );
	
}
}


#endif

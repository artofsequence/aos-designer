#ifndef HGUARD_AOSD_CORE_RESOURCEPROVIDER_H__
#define HGUARD_AOSD_CORE_RESOURCEPROVIDER_H__
#pragma once

#include <map>
#include "resourceptr.hpp"
#include "ResourceInfo.hpp"
#include "aosl/resource.hpp"

namespace aosd
{
namespace core
{
	
	class ResourceProvider
	{
	public:
		
		ResourcePtr get( const ResourceInfo& resource_infos );
		
		
	private:

		std::map< ResourceInfo, ResourcePtr > m_resources_registry;

		ResourcePtr find( const ResourceInfo& resource_infos );
		void add_resource( const ResourceInfo& resource_infos, ResourcePtr resource );

	};



}
}


#endif

#ifndef HGUARD_AOSD_BACKEND_RESOURCEPROVIDER_H__
#define HGUARD_AOSD_BACKEND_RESOURCEPROVIDER_H__
#pragma once

#include <map>
#include <aosdesigner/backend/resourceptr.hpp>
#include <aosdesigner/backend/resourceinfo.hpp>
#include <aosl/resource.hpp>

namespace aosd
{
namespace backend
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

#ifndef HGUARD_AOSD_BACKEND_RESOURCEPROVIDER_H__
#define HGUARD_AOSD_BACKEND_RESOURCEPROVIDER_H__
#pragma once

#include <map>
#include <aosdesigner/backend/resource/resourceptr.hpp>
#include <aosdesigner/backend/resource/resourceinfo.hpp>
#include <aosl/resource.hpp>

namespace aosd
{
namespace backend
{
	
	class ResourceProvider
	{
	public:
		
		ResourcePtr get( const ResourceInfo& resource_info );
		
		
	private:

		std::map< ResourceInfo, ResourcePtr > m_resources_registry;

		ResourcePtr find( const ResourceInfo& resource_info );
		void add_resource( const ResourceInfo& resource_info, ResourcePtr resource );

	};



}
}


#endif

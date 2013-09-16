#include <aosdesigner/backend/resource/resourceprovider.hpp>

#include <utilcpp/assert.hpp>

#include <aosdesigner/backend/resource/resourcefactory.hpp>

namespace aosd
{
namespace backend
{

	ResourcePtr ResourceProvider::get( const ResourceInfo& resource_info )
	{
		auto resource = find( resource_info );

		if( resource )
			return resource;

		resource = create_resource( resource_info );

		if( resource )
		{
			add_resource( resource_info, resource );
		}

		return resource;
	}

	ResourcePtr ResourceProvider::find( const ResourceInfo& resource_info )
	{
		auto resource_it = m_resources_registry.find( resource_info );
		if( resource_it != end(m_resources_registry) )
		{
			return resource_it->second;
		}
		return ResourcePtr();
	}

	void ResourceProvider::add_resource( const ResourceInfo& resource_info, ResourcePtr resource )
	{
		m_resources_registry.insert( std::make_pair( resource_info, resource ) );
	}


}
}
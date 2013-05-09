#include "resourcefactory.hpp"

#include <functional>
#include <map>

#include "utilcpp/assert.hpp"
#include "aosl/resource_type.hpp"

#include "resourceptr.hpp"
#include "resource.hpp"

namespace aosd
{
namespace core
{
	

	namespace 
	{
		typedef std::function< ResourcePtr ( const URI& resource_uri ) > ResourceFactory;
		typedef std::map< aosl::Resource_type, ResourceFactory > ResourceFactoryTable;

		ResourceFactoryTable build_resource_factory_table();

		const ResourceFactoryTable RESOURCE_FACTORY_TABLE = build_resource_factory_table();

		ResourceFactoryTable build_resource_factory_table()
		{
			ResourceFactoryTable table;

			table[ "auto" ] = []( const URI& uri ) { return ResourcePtr( new Resource_Unknow( uri, "unknown" ) ); };
			table[ "image" ] = []( const URI& uri ) { return ResourcePtr( new Resource_Unknow( uri, "image" ) ); };
			
			

			return table;
		};		


	}

	ResourcePtr create_resource( const ResourceInfo& resource_info )
	{
		auto factory_it = RESOURCE_FACTORY_TABLE.find( resource_info.type() );
		if( factory_it != end(RESOURCE_FACTORY_TABLE) )
		{
			auto factory = factory_it->second;
			return factory( resource_info.uri() );
		}

		return ResourcePtr();
	}

}
}
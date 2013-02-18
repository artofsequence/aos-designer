#ifndef HGUARD_AOSD_CORE_LIBRARY_HPP__
#define HGUARD_AOSD_CORE_LIBRARY_HPP__
#pragma once

#include <functional>
#include <algorithm>
#include <map>
#include <vector>

#include <boost/filesystem/path.hpp>

#include <aosl/resource_id.hpp>
#include "core/resources/ResourcePtr.hpp"
#include "core/resources/ResourceRef.hpp"

namespace aosl
{
	class Library;
}

namespace aosd
{
namespace core
{
	namespace bfs = boost::filesystem;

	/** Library of resources.
	**/
	class Library
	{
	public:

		Library();
		explicit Library( const aosl::Library& library_info );
		explicit Library( const bfs::path& file_path );
		~Library();

		/** Update the content of the library. **/
		void update( const aosl::Library& library_info );
				
		/** Import resources from another library. **/
		void import( const Library& library );

		void add( aosl::Resource_id resource_id, ResourcePtr resource );

		void clear();

		ResourcePtr find( const aosl::Resource_id& resource_id ) const;

		typedef std::function< void ( ResourceRef ) > ResourceFunc;
		void for_each_resource( ResourceFunc func ) const;
		
	private:

		std::map< aosl::Resource_id,  ResourcePtr > m_resource_registry;

		std::vector< ResourceRef > m_resources;

	};

}
}


#endif

#ifndef HGUARD_AOSD_BACKEND_LIBRARY_HPP__
#define HGUARD_AOSD_BACKEND_LIBRARY_HPP__
#pragma once

#include <functional>
#include <algorithm>
#include <map>
#include <vector>

#include <boost/filesystem/path.hpp>

#include <aosl/resource_id.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/resourceptr.hpp>
#include <aosdesigner/backend/resourceref.hpp>

namespace aosl
{
	class Library;
}

namespace aosd
{
namespace backend
{
	class Context;

	namespace bfs = boost::filesystem;

	/** Library of resources.
	**/
	class AOSD_BACKEND_API Library
	{
	public:

		explicit Library( Context& context );
		explicit Library( Context& context, const aosl::Library& library_info );
		explicit Library( Context& context, const bfs::path& file_path );
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
		Library( const Library& ); // = delete;
		Library& operator=( const Library& ); // = delete;

		Context& m_context;

		std::map< aosl::Resource_id,  ResourcePtr > m_resource_registry;

		std::vector< ResourceRef > m_resources;

	};

}
}


#endif

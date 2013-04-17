#include "library.hpp"


#include "core/context.hpp"
#include "core/resources/resource.hpp"
#include "aosl/library.hpp"

#include "utilcpp/assert.hpp"

namespace aosd
{
namespace core
{



	Library::Library()
	{

	}

	Library::Library( const aosl::Library& library_info )
	{
		update( library_info );
	}

	Library::Library( const bfs::path& file_path )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
	}

	Library::~Library()
	{

	}

	void Library::update( const aosl::Library& library_info )
	{
		clear();

		const auto& resource_list = library_info.resource();
		
		std::for_each( begin(resource_list), end(resource_list), [&]( const aosl::Resource& resource )
		{
			auto resource_object = Context::instance().resource_provider().get( resource );
			UTILCPP_ASSERT_NOT_NULL( resource_object ); // TODO : replace by exception?
			add( resource.id() , resource_object );
		});

		const auto& include_list = library_info.include();
		if( !include_list.empty() )
		{
			
			std::for_each( begin(include_list), end(include_list), [&]( const aosl::Library_include& import_info )
			{
				// build the library
				try
				{
					auto import_path = bfs::path( import_info.data() );
					auto library_to_import = std::unique_ptr<Library>( new Library( import_path ) );
					import( *library_to_import );
				}
				catch( const std::exception& e )
				{
					UTILCPP_LOG_ERROR << "Failed to load library at \"" << import_info.data() << "\" : " << e.what();
				}
				
			});
		}
		
	}

	void Library::import( const Library& library )
	{
		// TODO : replace by std::copy? does it work with maps?
		std::for_each( begin(library.m_resource_registry), end(library.m_resource_registry), [&]( std::pair< aosl::Resource_id, ResourcePtr > resource_it )
		{
			add( resource_it.first, resource_it.second );
		});
	}

	void Library::clear()
	{
		m_resource_registry.clear();
		m_resources.clear();
	}

	void Library::add( aosl::Resource_id resource_id, ResourcePtr resource )
	{
		if( resource && !resource_id.empty() )
		{
			auto success = m_resource_registry.insert( std::make_pair( resource_id, resource ) );
			if( success.second ) // inserted with success
			{
				m_resources.emplace_back( ResourceRef( resource_id, resource ) );
			}
			else
			{
				throw std::exception( "Failed to add resource!" );
			}
		}
		else
		{
			throw std::exception( "Tried to add invalid resource!" );
		}
	}

	ResourcePtr Library::find( const aosl::Resource_id& resource_id ) const
	{
		auto resource_it = m_resource_registry.find( resource_id );
		if( resource_it != end(m_resource_registry) )
		{
			UTILCPP_ASSERT_NOT_NULL( resource_it->second );
			return resource_it->second;
		}

		return ResourcePtr();
	}

	void Library::for_each_resource( ResourceFunc func ) const
	{
		std::for_each( begin(m_resources), end(m_resources), [&]( const ResourceRef& resource_ref ) 
		{
			UTILCPP_ASSERT_NOT_NULL( resource_ref.resource() );
			func( resource_ref );
		});
	}

}
}
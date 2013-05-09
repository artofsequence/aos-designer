#include <aosdesigner/backend/library.hpp>

#include <utilcpp/assert.hpp>

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/resource.hpp>
#include <aosl/library.hpp>


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
		
		for( const auto& resource : resource_list )
		{
			auto resource_object = Context::instance().resource_provider().get( resource );
			UTILCPP_ASSERT_NOT_NULL( resource_object ); // TODO : replace by exception?
			add( resource.id() , resource_object );
		}

		const auto& include_list = library_info.include();
		if( !include_list.empty() )
		{
			
			for( const auto& import_info : include_list )
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
				
			}
		}
		
	}

	void Library::import( const Library& library )
	{
		// TODO : replace by std::copy? does it work with maps?
		for( auto resource_it : library.m_resource_registry )
		{
			add( resource_it.first, resource_it.second );
		}
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
		for( const auto& resource_ref : m_resources )
		{
			UTILCPP_ASSERT_NOT_NULL( resource_ref.resource() );
			func( resource_ref );
		}
	}

}
}
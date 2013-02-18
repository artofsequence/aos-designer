#include "Resource.hpp"



namespace aosd
{
namespace core
{

	Resource::Resource( const URI& uri, const aosl::Resource_type& type )
		: m_type_name( type ) 
	{

	}

	Resource::~Resource()
	{

	}

	void Resource::load()
	{
		on_load();
	}

	void Resource::unload()
	{
		on_unload();
	}

}
}
#ifndef HGUARD_AOSD_BACKEND_RESOURCEREF_HPP__
#define HGUARD_AOSD_BACKEND_RESOURCEREF_HPP__
#pragma once

#include <aosdesigner/backend/resourceptr.hpp>
#include <aosl/resource_id.hpp>

namespace aosd
{
namespace backend
{
	class ResourceRef
	{
	public:
		ResourceRef( aosl::Resource_id id, ResourcePtr res ) : m_id( id ) , m_resource( res ) {  }

		ResourceRef( const ResourceRef&& other_ref ) : m_id( other_ref.m_id ), m_resource( std::move(other_ref.m_resource) ){}

		aosl::Resource_id id() const { return m_id; }
		ResourcePtr resource() const { return m_resource; }

	private:
		aosl::Resource_id m_id;
		ResourcePtr m_resource;
	};

}
}


#endif

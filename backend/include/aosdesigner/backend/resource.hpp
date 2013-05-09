#ifndef HGUARD_AOSD_CORE_RESOURCE_HPP__
#define HGUARD_AOSD_CORE_RESOURCE_HPP__
#pragma once

#include <string>

#include <boost/noncopyable.hpp>
#include <aosl/resource_type.hpp>

#include <aosdesigner/backend/uri.hpp>

namespace aosd
{
namespace core
{
	class Resource
		: public boost::noncopyable
	{
	public:

		virtual ~Resource();
		
		void load();
		void unload();


		const URI& uri() const { return m_uri; }
		const std::string& type_name() const { return m_type_name; }

	protected:

		explicit Resource( const URI& uri, const aosl::Resource_type& type );
		
		virtual void on_load() = 0;
		virtual void on_unload() = 0;

	private:

		const URI m_uri;
		const std::string m_type_name;
	};

	class Resource_Unknow
		: public Resource
	{
	public:
		
		Resource_Unknow( const URI& uri, const aosl::Resource_type& type ) : Resource( uri, type ){}

	private:
		void on_load(){}
		void on_unload(){}
	};

}
}


#endif

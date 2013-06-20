#ifndef HGUARD_AOSD_BACKEND_DATAPROVIDER_HPP__
#define HGUARD_AOSD_BACKEND_DATAPROVIDER_HPP__
#pragma once

#include <aosl/sequence.hpp>
#include <aosdesigner/backend/tools/uri.hpp>
#include <aosdesigner/backend/info/projectinfo.hpp>

namespace aosd {
namespace backend {
	
	/** Provide access to data from outside the backend.
		The way the data are retrieved is defined by the implementation.
		The implementation should be able to read data from files in the
		filesystem, from the network, from archives, etc.
	*/
	class DataProvider
	{
	public:

		ProjectInfo get_project_info( const URI& uri ) { return read_project_info( uri ); }
		
		aosl::Sequence get_aosl_sequence( const URI& uri ) { return read_aosl_sequence( uri ); }
		
		aosl::Library get_aosl_library( const URI& uri ) { return read_aosl_library( uri ); }
		
		template< class T >
		void save( const T& data, const URI& uri ) { write( data, uri ); }

	protected:
		DataProvider(){}			// = default;
		virtual ~DataProvider(){}	// = default;

		virtual ProjectInfo read_project_info( const URI& uri ) = 0;
		virtual void write( const ProjectInfo& info, const URI& uri ) = 0;

		virtual aosl::Sequence read_aosl_sequence( const URI& uri ) = 0;
		virtual void write( const aosl::Sequence& aosl_sequence, const URI& uri ) = 0;

		virtual aosl::Library read_aosl_library( const URI& uri ) = 0;
		virtual void write( const aosl::Library& aosl_library, const URI& uri ) = 0;
	};

}}


#endif

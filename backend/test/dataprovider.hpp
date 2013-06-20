#ifndef HGUARD_AOSD_BACKEND_TEST_DATAPROVIDER_HPP__
#define HGUARD_AOSD_BACKEND_TEST_DATAPROVIDER_HPP__

#include <aosdesigner/backend/dataprovider.hpp>
#include <aosdesigner/backend/info/projectinfo.hpp>

namespace aosd {
namespace backend {

	class DummyDataProvider 
		: public DataProvider
	{
	public:

	private:

		ProjectInfo read_project_info( const URI& uri ) override
		{
			ProjectInfo project_info;
			// ...
			return project_info;
		}

		void write( const ProjectInfo& info, const URI& uri ) override;

		aosl::Sequence read_aosl_sequence( const URI& uri ) override;
		void write( const aosl::Sequence& aosl_sequence, const URI& uri ) override;

		aosl::Library read_aosl_library( const URI& uri ) override;
		void write( const aosl::Library& aosl_library, const URI& uri ) override;

	};

}}


#endif
#ifndef HGUARD_AOSD_BACKEND_TEST_DATAPROVIDER_HPP__
#define HGUARD_AOSD_BACKEND_TEST_DATAPROVIDER_HPP__

#include <aosdesigner/backend/dataprovider.hpp>
#include <aosdesigner/backend/info/projectinfo.hpp>

#include <aosl/sequence.hpp>
#include <aosl/library.hpp>
#include <aoslcpp/algorithm/edition.hpp>

namespace aosd {
namespace backend {

	class DummyDataProvider 
		: public DataProvider
	{

		ProjectInfo read_project_info( const URI& uri ) override;

		void write( const ProjectInfo& info, const URI& uri ) override;

		aosl::Sequence read_aosl_sequence( const URI& uri ) override;
		void write( const aosl::Sequence& aosl_sequence, const URI& uri ) override;

		aosl::Library read_aosl_library( const URI& uri ) override;
		void write( const aosl::Library& aosl_library, const URI& uri ) override;

	};

	inline ProjectInfo DummyDataProvider::read_project_info( const URI& )
	{
		
		ProjectInfo dummy_info;
		dummy_info.id = make_new_id<Project>();
		dummy_info.name = "Dummy Project";
		
		dummy_info.sequence_list.reserve( 2 );
		dummy_info.editor_list.reserve( 2 );

		dummy_info.sequence_list.emplace_back();
		SequenceInfo& sequence_a = dummy_info.sequence_list.back();
		sequence_a.id = make_new_id<Sequence>();
		sequence_a.aosl_location = "somewhere";
		sequence_a.name = "Dummy Sequence A";

		dummy_info.sequence_list.emplace_back();
		SequenceInfo& sequence_b = dummy_info.sequence_list.back();
		sequence_b.id = make_new_id<Sequence>();
		sequence_b.aosl_location = "somewhereelse";
		sequence_b.name = "Dummy Sequence B";
		
		dummy_info.editor_list.emplace_back();
		EditorInfo& editor_a_1 = dummy_info.editor_list.back();
		editor_a_1.id = make_new_id<Editor>();
		editor_a_1.sequence_id = sequence_a.id;

		dummy_info.editor_list.emplace_back();
		EditorInfo& editor_a_2 = dummy_info.editor_list.back();
		editor_a_2.id = make_new_id<Editor>();
		editor_a_2.sequence_id = sequence_a.id;

		return dummy_info;
	}

	inline aosl::Sequence DummyDataProvider::read_aosl_sequence( const URI& )
	{
		return aoslcpp::make_empty_sequence( "Dummy Sequence" );
	}

	inline aosl::Library DummyDataProvider::read_aosl_library( const URI& )
	{
		return aosl::Library();
	}

	inline void DummyDataProvider::write( const ProjectInfo&, const URI& )
	{
		// do nothing
	}

	inline void DummyDataProvider::write( const aosl::Sequence&, const URI& )
	{
		// do nothing
	}

	inline void DummyDataProvider::write( const aosl::Library&, const URI& )
	{
		// do nothing
	}

}}


#endif
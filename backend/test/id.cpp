#include <gtest/gtest.h>

#include <vector>
#include <map>
#include <fstream>
#include <cstdio>
#include <unordered_map>
#include <aosdesigner/backend/id.hpp>


using namespace aosd::backend;

typedef Id<int> IntId;
typedef Id<float> FloatId;

TEST( Test_Id, default_id_is_invalid )
{
	IntId k;
	ASSERT_FALSE( k.is_valid() );
	ASSERT_FALSE( is_valid( k ) );

}

TEST( Test_Id, generated_id_is_valid )
{
	IntId k = make_id<int>();
	ASSERT_TRUE( k.is_valid() );
	ASSERT_TRUE( is_valid( k ) );
}


TEST( Test_Id, generated_ids_are_unique )
{
	IntId k = make_id<int>();
	IntId l = make_id<int>();
	
	ASSERT_TRUE( is_valid( k ) );
	ASSERT_TRUE( is_valid( l ) );
	ASSERT_NE( k, l );
}

TEST( Test_Id, can_be_used_as_index )
{
	std::map< IntId, IntId > id_map;
	id_map[ make_id<int>() ] = make_id<int>();
	auto find_it = id_map.find( make_id<int>() );
	id_map.clear();
}

TEST( Test_Id, can_be_used_as_hashed_index )
{
	std::unordered_map< IntId, IntId > id_map;
	id_map[ make_id<int>() ] = make_id<int>();
	auto find_it = id_map.find( make_id<int>() );
	id_map.clear();
}

TEST( Test_Id, text_serialization )
{
	auto k = make_id<int>();
	std::string text = to_string(k);
	auto l = to_id<int>( text );
	ASSERT_EQ( k, l );
}

TEST( Test_Id, byte_serialization )
{
	static const auto file_name = "test.test";

	auto k = make_id<int>();
	decltype(k) l;

	{
		std::ofstream fout( file_name, std::ios_base::binary ) ;
		fout << k;
	}
	{
		std::ifstream fout( file_name, std::ios_base::binary ) ;
		fout >> l;
	}
	remove( file_name );
	
	ASSERT_EQ( k, l );
}


TEST( Test_Id, check_lot_of_ids )
{
	std::vector<IntId> ids( 1000 );
	
	for( auto& id : ids )
		ASSERT_FALSE( is_valid(id) );

	for( auto& id : ids )
	{
		id = make_id<int>();
		ASSERT_TRUE( is_valid(id) );
	}

	for( size_t idx = 0, end_idx = ids.size(); idx < end_idx; ++idx )
	{
		auto id = ids[idx];
		ASSERT_TRUE( is_valid(id) );

		for( size_t other_idx = 0; other_idx < end_idx; ++other_idx)
		{
			if( idx == other_idx )
				continue;
			auto other_id = ids[other_idx];
			ASSERT_TRUE( is_valid(other_id) );

			ASSERT_NE( id, other_id );
		}
	}
	
}

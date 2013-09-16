#include "aoslcpp/algorithm/edition.hpp"

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "aosl/aosl.hpp"

namespace aoslcpp
{
	const std::string DEFAULT_SEQUENCE_ID_PREFIX( "sequence-" );
	const std::string DEFAULT_FIRST_STAGE_NAME( "stage_0" );

	aosl::Sequence make_empty_sequence( const std::string& sequence_name, const std::string& sequence_id, const std::string& fist_stage_id )
	{
		aosl::Library library;

		aosl::Canvas::AreaType area;
		area.x( 1.0 );
		area.y( 1.0 );
		area.z( 1.0 );

		aosl::Canvas::ObjectsType objects;
		auto canvas = aosl::Canvas( area, objects );

		aosl::Navigation navigation;
		aosl::Story::MovesType moves;

		const std::string root_stage_id= fist_stage_id.empty() ? DEFAULT_FIRST_STAGE_NAME : fist_stage_id;
		auto root_stage = aosl::Stage( aosl::Stage_id(root_stage_id) );

		aosl::Story::StagesType stages;
		stages.stage().push_back( root_stage );

		auto story = aosl::Story( stages, moves, aosl::Stage_ref(root_stage_id) );

		auto unique_id = aosl::Unique_id( sequence_id );

		if( sequence_id.empty() )
		{
			static boost::uuids::random_generator new_sequence_id_generator;
			unique_id = aosl::Unique_id( DEFAULT_SEQUENCE_ID_PREFIX + to_string( new_sequence_id_generator() ) );
		}
		
		return aosl::Sequence( library, canvas, story, sequence_name, unique_id );
	}

}
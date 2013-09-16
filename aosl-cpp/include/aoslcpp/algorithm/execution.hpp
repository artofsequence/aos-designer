#ifndef HGUARD_AOSLCPP_EXECUTION_HPP__
#define HGUARD_AOSLCPP_EXECUTION_HPP__
#pragma once

#include <boost/optional.hpp>
#include "aosl/aosl_forward.hpp"
#include "aosl/object_ref.hpp"

namespace aoslcpp
{
	
	void activate( aosl::Object& object );
	void deactivate( aosl::Object& object );
	void switch_state( aosl::Object& object );

	
	void activate( aosl::Canvas& canvas, const aosl::Object_ref& object_ref );
	void deactivate( aosl::Canvas& canvas, const aosl::Object_ref& object_ref );
	void switch_state( aosl::Canvas& canvas, const aosl::Object_ref& object_ref );

	void transform( aosl::Properties_graphic_object& graphic_properties, const aosl::Transformation& transformation );
	void transform( aosl::Canvas& canvas, const aosl::Object_ref& object_ref, const aosl::Transformation& transformation );

	void execute( const aosl::Change& change, aosl::Object& object, bool reverse = false );
	void execute( aosl::Canvas& canvas, const aosl::Change& change, bool reverse = false );
	void execute( aosl::Canvas& canvas, const aosl::Move& move, bool reverse = false );


	inline void reverse_activate( aosl::Object& object ) { deactivate( object ); }
	inline void reverse_deactivate( aosl::Object& object ) { activate( object ); }
	inline void reverse_switch_state( aosl::Object& object ) { switch_state( object ); }
	inline void reverse_activate( aosl::Canvas& canvas, const aosl::Object_ref& object_ref ) { deactivate( canvas, object_ref ); }
	inline void reverse_deactivate( aosl::Canvas& canvas, const aosl::Object_ref& object_ref ) { activate( canvas, object_ref ); }
	inline void reverse_switch_state( aosl::Canvas& canvas, const aosl::Object_ref& object_ref ) { switch_state( canvas, object_ref ); }

	void reverse_transform( aosl::Properties_graphic_object& graphic_properties, const aosl::Transformation& transformation );
	void reverse_transform( aosl::Canvas& canvas, const aosl::Object_ref object_ref, const aosl::Transformation& transformation );
	

	/** Deduce automatically what would be the next move.
		@return The next move if it's there is only one available from the stage, null otherwise.
	**/
	boost::optional< aosl::Move > auto_next( const aosl::Story& story, const aosl::Stage& stage );
	boost::optional< aosl::Move > auto_next( const aosl::Story& story, const aosl::Stage_ref& stage_ref );

}


#endif
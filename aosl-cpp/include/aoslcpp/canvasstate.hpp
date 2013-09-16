#ifndef HGUARD_AOSLCPP_CANVASSTATE_HPP__
#define HGUARD_AOSLCPP_CANVASSTATE_HPP__
#pragma once

#include <vector>
#include <functional>

#include "aosl/object_ref.hpp"
#include "aosl/canvas.hpp"
#include "aosl/transformation_forward.hpp"

namespace aosl { class Change; class Move; }

namespace aoslcpp
{
	/** Describe a state of a canvas.
	**/
	class CanvasState
	{
	public:

		explicit CanvasState( const aosl::Canvas& canvas );

		void activate( const aosl::Object_ref& object_ref );
		void deactivate( const aosl::Object_ref& object_ref );
		void switch_state( const aosl::Object_ref& object_ref );

		void transform( const aosl::Object_ref& object_ref, const aosl::Transformation& transformation );

		void execute( const aosl::Change& change, bool reverse = false );
		void execute( const aosl::Move& move, bool reverse = false );

		const aosl::Canvas& canvas() const { return m_canvas; }
		
	private:

		aosl::Canvas m_canvas;

	};


}


#endif

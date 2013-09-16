#include "aoslcpp/canvasstate.hpp"

#include "aoslcpp/algorithm/execution.hpp"

#include "aosl/change.hpp"

namespace aoslcpp
{
	
	
	CanvasState::CanvasState( const aosl::Canvas& canvas )
		: m_canvas( canvas )
	{
	}
	
	void CanvasState::activate( const aosl::Object_ref& object_ref )
	{
		aoslcpp::activate( m_canvas, object_ref );
	}

	void CanvasState::deactivate( const aosl::Object_ref& object_ref )
	{
		aoslcpp::deactivate( m_canvas, object_ref );
	}

	void CanvasState::switch_state( const aosl::Object_ref& object_ref )
	{
		aoslcpp::switch_state( m_canvas, object_ref );
	}

	void CanvasState::transform( const aosl::Object_ref& object_ref, const aosl::Transformation& transformation )
	{
		aoslcpp::transform( m_canvas, object_ref, transformation );
	}

	void CanvasState::execute( const aosl::Change& change, bool reverse )
	{
		aoslcpp::execute( m_canvas, change, reverse );
	}

	void CanvasState::execute( const aosl::Move& move, bool reverse )
	{
		aoslcpp::execute( m_canvas, move, reverse );
	}

}
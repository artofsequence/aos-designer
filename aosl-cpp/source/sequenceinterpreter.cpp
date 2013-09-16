#include "aoslcpp/sequenceinterpreter.hpp"

#include <algorithm>

#include "utilcpp/assert.hpp"

#include "aoslcpp/algorithm/find.hpp"
#include "aoslcpp/algorithm//execution.hpp"
#include "aosl/sequence.hpp"
#include "aosl/event.hpp"

namespace aoslcpp
{
		
	SequenceInterpreter::SequenceInterpreter( const aosl::Sequence& sequence )
		: m_story( sequence.story() ) 
		, m_path()
		, m_canvas( sequence.canvas() ) // copy the initial canvas
		, m_navigation( sequence.story().navigation() ? *sequence.story().navigation() : aosl::Navigation() ) // empty navigation if not provided by the sequence
	{
		// deduce the automatic next move if any
		if( !m_story.stages().stage().empty() )
		{
			m_auto_next_move = auto_next( story(), aosl::Stage_ref( m_story.stages().stage().front().id() ) );
		}

	}

	void SequenceInterpreter::go( const aosl::Event& event )
	{
		go( event.move() );
	}

	aosl::Stage_ref SequenceInterpreter::execute_move( const aosl::Move_ref& move_ref, bool reverse )
	{
		// get the move informations
		const auto move = find_move( story(), move_ref );
		UTILCPP_ASSERT_NOT_NULL( move );

		return execute_move( *move, reverse );
	}

	aosl::Stage_ref SequenceInterpreter::execute_move( const aosl::Move& move, bool reverse )
	{
		const aosl::Stage_ref stage_ref = reverse ? move.from().front() : move.to(); // TODO: THIS IS WRONG!! a reverse execution of a move should know what was the source stage in the path!

		// get the next stage informations
		const auto stage = find_stage( story(), stage_ref );
		UTILCPP_ASSERT_NOT_NULL( stage );

		// apply the changes
		m_canvas.execute( move, reverse );

		// update the navigation options
		if( stage->navigation() )
			m_navigation.update( *stage->navigation() );
		else
			m_navigation.reset();

		// deduce the automatic next move if any
		m_auto_next_move = auto_next( story(), stage_ref );

		return stage_ref;
	}

	void SequenceInterpreter::go( const aosl::Move_ref& move_ref )
	{
		const auto move = find_move( story(), move_ref );
		UTILCPP_ASSERT_NOT_NULL( move );

		const auto stage_ref = execute_move( move_ref, false );
		m_path.add_step( move->id(), stage_ref );
	}

	void SequenceInterpreter::go( const aosl::Move& move )
	{
		const auto stage_ref = execute_move( move, false );
		m_path.add_step( move.id(), stage_ref );
	}

	void SequenceInterpreter::go_back( std::size_t step_count )
	{
		UTILCPP_ASSERT( step_count > 0, "Invalid step count for going back : " << step_count );

		if( can_go_back() && step_count > 0 )
		{
			const auto stage_ref = execute_move( m_path.last_move(), true );
			m_path.step_back( 1 );

			UTILCPP_ASSERT( m_path.current_stage() == stage_ref, "WTF????" );

			--step_count;
		}
	}

	void SequenceInterpreter::go_next()
	{
		if( can_go_next() )
		{
			// find the unique move to go next
			go( *m_auto_next_move );
		}

		
	}


}
#include "aoslcpp/storypath.hpp"

#include "utilcpp/assert.hpp"

namespace aoslcpp
{

	void StoryPath::add_step( aosl::Move_ref move_ref, aosl::Stage_ref stage_ref )
	{
		Step step = { move_ref, stage_ref };
		m_steps.emplace_back( step );
	}

	void StoryPath::step_back( std::size_t step_count )
	{
		UTILCPP_ASSERT( step_count > 0, "Invalid step count for stepping back : " << step_count );

		while( can_step_back() && step_count != 0 ) // we need to have at least one step
		{
			m_steps.pop_back();
			--step_count;
		}

	}

	void StoryPath::for_each_step( std::function< void ( const Step& ) > f ) const
	{
		for( const auto& step : m_steps )
			f( step );
	}

}
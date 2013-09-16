#ifndef HGUARD_AOSLCPP_STORYPATH_HPP__
#define HGUARD_AOSLCPP_STORYPATH_HPP__
#pragma once

#include <vector>
#include <functional>

#include "aosl/stage_ref.hpp"
#include "aosl/move_ref.hpp"


namespace aoslcpp
{
	/** Path walk through a story. 
		Record of steps done to walk through a sequence story.
	**/
	class StoryPath
	{
	public:
		
		/// A step contain a reference to a stage where the step is and a reference to the move that was used to get there.
		struct Step
		{
			aosl::Move_ref move;
			aosl::Stage_ref stage;
		};
		
		/** Add a setp to the path.
			@param move_ref		The move used to go through this step.
			@param stage_ref	The stage where we got once the step is done.
		**/
		void add_step( aosl::Move_ref move_ref, aosl::Stage_ref stage_ref );

		/** Step back in the path and return the last.
			If we try to do more steps backward than recored
			@param step_count	Count of steps to do backward. 
		*/
		void step_back( std::size_t step_count = 1 );

		/** @return The current stage. */
		aosl::Stage_ref current_stage() const { return m_steps.empty() ? aosl::Stage_ref("") : m_steps.back().stage; }

		/** @return The last move through which we go to the current stage. */
		aosl::Move_ref last_move() const { return m_steps.empty() ? aosl::Move_ref("") : m_steps.back().move; }
		
		/** @return Count of steps we've gone through. */
		std::size_t step_count() const { return m_steps.size(); }
		
		/** @return True if we can step back, false otherwise. */
		bool can_step_back() const { return !m_steps.empty(); }
		
		/** @return True if there is no step in this path, false otherwise. */
		bool empty() const { return m_steps.empty(); }

		/**  */
		void for_each_step( std::function< void ( const Step& ) > ) const;

	private:

		/// Steps which the story have been walked through.
		std::vector< Step > m_steps;
				
	};


}


#endif

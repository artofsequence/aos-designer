#ifndef HGUARD_AOSLCPP_NAVIGATIONSTATE_HPP__
#define HGUARD_AOSLCPP_NAVIGATIONSTATE_HPP__
#pragma once

#include "aosl/navigation.hpp"

namespace aoslcpp
{
	/** Provide the current navigation choices at a specific stage in a sequence's story.
	*/
	class NavigationState
	{
	public:

		explicit NavigationState( const aosl::Navigation& default_navigation );


		/** Update the navigation options with the default options plus the provided stage navigation options. */
		void update( const aosl::Navigation& stage_navigation );

		/** Reset the navigation to the default options. */
		void reset();
		
		const aosl::Navigation& current() const { return m_current_navigation; }


	private:

		aosl::Navigation m_default_navigation;
		aosl::Navigation m_current_navigation;

	};


}


#endif

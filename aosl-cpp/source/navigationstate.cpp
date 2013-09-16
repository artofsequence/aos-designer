#include "aoslcpp/navigationstate.hpp"

#include <algorithm>

namespace aoslcpp
{
	NavigationState::NavigationState( const aosl::Navigation& default_navigation )
		: m_default_navigation( default_navigation )
		, m_current_navigation( default_navigation )
	{

	}

	void NavigationState::reset()
	{
		m_current_navigation = m_default_navigation;
	}

	void NavigationState::update( const aosl::Navigation& stage_navigation )
	{
		reset();

		const auto& stage_events = stage_navigation.event();

		for( const auto& event : stage_events )
		{
			m_current_navigation.event().push_back( event );
		};
		

	}


}
#ifndef HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__
#define HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__

#include <aosdesigner/backend/id.hpp>

namespace aosd {
namespace backend {

	class EventDispatcher
	{
	public:

		template< class EventType >
		void publish( EventType event )
		{
			m_event_queue.push( [=]{
				dispatch( event );
			});
		}

	private:
		WorkQueue m_event_queue;

		template< class EventType >
		void dispatch( const EventType& )
		{
			find the list of listeners
			dispatch the event to listeners
		}
	};

}}

#endif

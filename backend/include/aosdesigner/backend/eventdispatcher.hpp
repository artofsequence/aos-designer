#ifndef HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__
#define HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__

#include <typeindex>
#include <tbb/concurrent_unordered_map.h>
#include <boost/signals2/signal.hpp>
#include <boost/signals2/connection.hpp>

#include <utilcpp/assert.hpp>
#include <aosdesigner/backend/workqueue.hpp>


namespace aosd {
namespace backend {

	

	class EventDispatcher
	{
	public:
		typedef boost::signals2::connection Connection;		
		typedef boost::signals2::scoped_connection ScopedConnection;

		EventDispatcher(){} // = default

		template< class EventType >
		void push( EventType event )
		{
			m_event_queue.push( [=]{
				dispatch( event );
			});
			
		}

		void dispatch()
		{
			m_event_queue.execute();
		}

		template< class EventType, class ObserverType >
		Connection connect( ObserverType&& observer )
		{
			auto observers = find_or_create_observers<EventType>();
			return observers->connect( std::forward<ObserverType>(observer) );
		}

	private:
		EventDispatcher( const EventDispatcher& ); // = delete;
		EventDispatcher& operator=( const EventDispatcher& ); // = delete;

		class ObserverGroup 
		{ 
			ObserverGroup( const ObserverGroup& ); // = delete;
			ObserverGroup& operator=( const ObserverGroup& ); // = delete;
		protected:
			ObserverGroup(){} // = default;
		};
		typedef std::shared_ptr<ObserverGroup> ObserverGroupPtr;

		WorkQueue<void> m_event_queue;
		typedef tbb::concurrent_unordered_map< std::type_index, ObserverGroupPtr > ObserversIndex;
		ObserversIndex m_observers_index;


		template< class EventType >
		class EventObservers : public ObserverGroup
		{
			static const EventType* dummy() { return nullptr; }

			boost::signals2::signal< void( EventType )> m_signal;
			
		public:
			void dispatch( const EventType& event )
			{
				m_signal( event );
			}

			template< class ObserverType >
			auto connect( ObserverType&& observer ) -> typename std::conditional< true, Connection, decltype( observer( *dummy() ) ) >::type
			{
				return m_signal.connect( std::forward<ObserverType>(observer) );
			}

			template< class ObserverType >
			auto connect( ObserverType observer ) -> typename std::conditional< true, Connection, decltype( observer() ) >::type
			{
				return m_signal.connect( [=]( const EventType&){ observer(); } );
			}

		};

		template< class EventType >
		void dispatch( const EventType& event )
		{
			auto observers = find_observers<EventType>();
			if( observers )
			{
				observers->dispatch( event );
			}			
		}

		template< class EventType >
		std::shared_ptr<EventObservers<EventType>> find_observers()
		{
			auto find_it = m_observers_index.find( typeid(EventType) );
			if( find_it != end(m_observers_index) )
				return std::static_pointer_cast< EventObservers<EventType> >( find_it->second );
			else
				return nullptr;
		}

		template< class EventType >
		std::shared_ptr<EventObservers<EventType>> create_observer_group()
		{
			auto new_group = std::make_shared<EventObservers<EventType>>();
			auto insert_info = m_observers_index.insert( std::make_pair( std::type_index(typeid(EventType)), new_group ) );
			UTILCPP_ASSERT( insert_info.second == true, "Tried to register a new observer group but there is already an observer group! Type: " 
				<< typeid(EventType).name() );
			return std::static_pointer_cast< EventObservers<EventType> >( insert_info.first->second );
		}

		template< class EventType >
		std::shared_ptr<EventObservers<EventType>> find_or_create_observers()
		{
			auto observers = find_observers<EventType>();
			if( !observers )
				observers = create_observer_group<EventType>();
			UTILCPP_ASSERT_NOT_NULL( observers );
			return observers;
		}

		
	};

}}

namespace tbb
{
	template<>
	size_t tbb_hasher( const std::type_index& idx )
	{ 
		return std::hash<std::type_index>()( idx );
	}

}

#endif

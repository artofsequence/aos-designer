#ifndef HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__
#define HGUARD_AOSD_BACKEND_EVENTDISPATCHER_HPP__

#include <typeindex>
#include <boost/signals2/signal.hpp>
#include <boost/signals2/connection.hpp>
#include <tbb/concurrent_unordered_map.h>
#include <utilcpp/assert.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>


namespace aosd {
namespace backend {

    class EventDispatcher
    {
    public:
        typedef boost::signals2::connection Connection;
        typedef boost::signals2::scoped_connection ScopedConnection;



        template< class EventType, class ObserverType >
        Connection on( ObserverType&& observer )
        {
            auto observers = find_or_create_observers<EventType>();
            return observers->connect( std::forward<ObserverType>(observer) );
        }

    protected:


        EventDispatcher(){}
        ~EventDispatcher(){}


        template< class EventType >
        size_t dispatch( const EventType& event )
        {
            if( auto observers = find_observers<EventType>() )
            {
                return observers->dispatch( event );
            }
            return 0;
        }

        template< class EventType >
        unsigned int operator()( const EventType& event ) { return dispatch( std::forward<EventType>(event) ); }


    private:
        EventDispatcher( const EventDispatcher& );
        EventDispatcher& operator=( const EventDispatcher& );

        
        class ObserverGroup 
        { 
        private:
            ObserverGroup( const ObserverGroup& );
            ObserverGroup& operator=( const ObserverGroup& );
        protected:
            ObserverGroup() {}
        };
        typedef std::shared_ptr<ObserverGroup> ObserverGroupPtr;

        typedef tbb::concurrent_unordered_map< std::type_index, ObserverGroupPtr > ObserversIndex;
        ObserversIndex m_observers_index;


        template< class EventType >
        class EventObservers : public ObserverGroup
        {
            static const EventType* dummy() { return nullptr; }
            typedef boost::signals2::signal< void( EventType )> Signal;

            Signal m_signal;

        public:

            size_t dispatch( const EventType& event )
            {
                m_signal( event );
                return m_signal.num_slots();
            }

            template< class ObserverType >
            auto connect( ObserverType&& observer )
                -> typename std::conditional< true, Connection, decltype( observer( *dummy() ) ) >::type
            {
                return m_signal.connect( std::forward<ObserverType>(observer) );
            }

            template< class ObserverType >
            auto connect( ObserverType observer ) 
                -> typename std::conditional< true, Connection, decltype( observer() ) >::type
            {
                return m_signal.connect( [=]( const EventType& ){ observer(); } );
            }


        };

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

    class EventDispatcher_Immediate
        : public EventDispatcher
    {
    public:
        
        using EventDispatcher::dispatch;
        using EventDispatcher::operator();

    };

    class EventDispatcher_Queued
        : public EventDispatcher
    {
    public:

        template< class EventType >
        void publish( EventType event )
        {
            m_event_queue.push( [=]{ EventDispatcher::dispatch( event ); } );
        }

        template< class EventType >
        void operator()( EventType&& event ) { publish( std::forward<EventType>(event) ); }

        void dispatch()
        {
            m_event_queue.execute();
        }
        
    private:

        WorkQueue<void> m_event_queue;
    };


}}

namespace tbb
{
    inline size_t tbb_hasher( const std::type_index& idx )
    { 
        return std::hash<std::type_index>()( idx );
    }

}

#endif

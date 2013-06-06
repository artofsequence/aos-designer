#ifndef HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#pragma once

#include <atomic>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/workqueue.hpp>
#include <aosdesigner/backend/eventdispatcher.hpp>

namespace aosd { 
namespace backend {

	template< class T >
	class WorkspaceObject
	{
	public:

		Id<T> id() const { return m_id; }

		template< class EventType, class ObserverType >
		EventDispatcher::Connection on( ObserverType&& observer )
		{
			return m_workspace.event_dispatcher().connect<EventType>( id(), std::forward<ObserverType>(observer) );
		}

	protected:
		explicit WorkspaceObject( Workspace& workspace )
			: m_workspace( workspace )
		{}

		~WorkspaceObject(){} // = default;

		template< class TaskType >
		auto push_task( TaskType task ) -> boost::future< decltype(task()) >;

		template< class TaskType >
		auto schedule( TaskType&& task ) -> boost::future< decltype(task()) > 
		{ return m_workspace.schedule( std::forward<TaskType>(task) ); }

		void execute_tasks() { m_work_queue.execute(); }

		void set_id( const Id<T>& new_id ) { m_id = new_id; }

		template< class EventType >
		void publish( EventType&& e )
		{
			m_workspace.event_dispatcher().publish( id(), e );
		}

	private:
		WorkspaceObject( const WorkspaceObject& ); // = delete;
		WorkspaceObject& operator=( const WorkspaceObject& ); // = delete;

		WorkQueue<void> m_work_queue;
		std::atomic<Id<T>> m_id;
		Workspace& m_workspace;

		template< class TaskType, class ReturnType >
		void execute_task( boost::promise<ReturnType>& promise, TaskType& task )
		{
			promise.set_value( task() );
		}

		template< class TaskType >
		void execute_task( boost::promise<void>& promise, TaskType& task )
		{
			task();
			promise.set_value();
		}

	};
	
	template< class T >
	template< class TaskType >
	auto WorkspaceObject<T>::push_task( TaskType task ) -> boost::future< decltype(task()) >
	{		
		typedef decltype(task()) ResultType;

		auto promise = std::make_shared<boost::promise<ResultType>>(); // TODO: c++14 allow moving in lambda instead of having to do this
		auto result = promise->get_future();

		m_work_queue.push( [promise, task]
		{ 
			try
			{
				detail::execute_task( *promise, task );
			}
			catch( ... )
			{
				promise->set_exception( boost::current_exception() );
			}			
		});

		return std::move(result); // TODO: remove move() it is implicit but current version of VS is buggy
	}

}}

#endif
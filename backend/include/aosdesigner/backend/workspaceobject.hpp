#ifndef HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#pragma once

#include <atomic>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/workqueue.hpp>
#include <aosdesigner/backend/async.hpp>

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
		auto schedule( TaskType&& task ) -> boost::future< decltype(task()) >
		{
			return async_impl( m_work_queue, std::forward<TaskType>(task) );
		}

		template< class TaskType >
		auto async( TaskType&& task ) -> boost::future< decltype(task()) > 
		{ return m_workspace.async( std::forward<TaskType>(task) ); }

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

		mutable WorkQueue<void> m_work_queue;
		std::atomic<Id<T>> m_id;
		Workspace& m_workspace;


	};
	

}}

#endif
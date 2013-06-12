#ifndef HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#pragma once

#include <atomic>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/tools/async.hpp>

namespace aosd { 
namespace backend {

	template< class T >
	class WorkspaceObject
	{
	public:

		Id<T> id() const { return m_id; }

		template< class EventType, class ObserverType >
		EventDispatcher::Connection on( ObserverType&& observer );

	protected:
		explicit WorkspaceObject( Workspace& workspace )
			: m_workspace( workspace )
		{}

		~WorkspaceObject(){} // = default;

		template< class TaskType >
		auto schedule( TaskType&& task ) -> future< decltype(task()) >;

		template< class TaskType >
		auto async( TaskType&& task ) -> future< decltype(task()) >;

		void execute_tasks();

		void set_id( const Id<T>& new_id ) { m_id = new_id; }

		template< class EventType >
		void publish( EventType&& e );

		Workspace& workspace() { return m_workspace; }

	private:
		WorkspaceObject( const WorkspaceObject& ); // = delete;
		WorkspaceObject& operator=( const WorkspaceObject& ); // = delete;

		mutable WorkQueue<void> m_work_queue;
		std::atomic<Id<T>> m_id;
		Workspace& m_workspace;


	};

	template< class T >
	template< class EventType, class ObserverType >
	EventDispatcher::Connection WorkspaceObject<T>::on( ObserverType&& observer )
	{
		return m_workspace.m_event_dispatcher.on<EventType>( id(), std::forward<ObserverType>(observer) );
	}

	template< class T >
	template< class TaskType >
	auto WorkspaceObject<T>::schedule( TaskType&& task ) -> future< decltype(task()) >
	{
		auto result = async_impl( m_work_queue, std::forward<TaskType>(task) );
		m_workspace.request_update();
		return result;
	}

	template< class T >
	template< class TaskType >
	auto WorkspaceObject<T>::async( TaskType&& task ) -> future< decltype(task()) > 
	{ 
		return m_workspace.async( std::forward<TaskType>(task) ); 
	}

	template< class T >
	void WorkspaceObject<T>::execute_tasks()
	{ 
		m_work_queue.execute(); 
		if( !m_work_queue.empty() )
			m_workspace.request_update();
	}


	template< class T >
	template< class EventType >
	void WorkspaceObject<T>::publish( EventType&& e )
	{
		m_workspace.m_event_dispatcher.publish( id(), e );
	}


}}

#endif
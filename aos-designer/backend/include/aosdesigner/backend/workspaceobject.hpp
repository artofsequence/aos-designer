#ifndef HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#define HGUARD_AOSD_BACKEND_WORKSPACEOBJECT_HPP__
#pragma once

#include <sstream>
#include <boost/thread/future.hpp>

#include <aosdesigner/backend/workspace.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/tools/workqueue.hpp>
#include <aosdesigner/backend/tools/async.hpp>

namespace aosd { 
namespace backend {

	/** CRTP base for types managed by the Workspace.
		Inject several public and protected services common to all 
		objects into the workspace:
		 - event dispatching (into the related workspace event dispatcher);
		 - access to the related workspace;
		 - a work queue automatically scheduling execution ASAP through the workspace update cycle;

		@remark Unless explicitly specified, all the member functions are thread-safe.
	*/
	template< class T >
	class WorkspaceObject
	{
		static T* dummy() { return nullptr; }
	public:

		/** @return Unique identifier of this object. */
		const Id<T>& id() const { return m_id; }

		/** Event handling connection.
			The observer will get events which source is specific object.
			The events are processed by the Workspace EventQueueDispatcher,
			this is only a shortcut that can be used if you already have access to the object.
			@see EventQueueDispatcher for details.

			Usage (with a fictive event):
			@code
				workspace_object.on<UpdateEvent>( []( const UpdateEvent& ev ){ 
					log( "Object Updated: " << ev.object_name );
				});

				// this is equivalent to the previous code

				workspace.event_dispatcher().on<UpdateEvent>( object_id, []( const UpdateEvent& ev ){ 
					log( "Object Updated: " << ev.object_name );
				});
			@endcode

			@param observer		An callable object which can take the EventType as argument.
			@return A connection object, used to disconnect the observer later if necessary.
		*/
		template< class EventType, class ObserverType >
		EventDispatcher::Connection on( ObserverType&& observer );

		/** @return Access to the object's workspace. */
		Workspace& workspace() { return m_workspace; }
		
		/** Add a task to be executed on the next object's update cycle.
			The task will be executed in sync with the update.
			@param task				Callable object which can take this object's reference as parameter. task( T& )
			@return The result of task once executed.
		*/
		template< class TaskType >
		auto on_next_update( TaskType task ) -> future< decltype(task( *dummy() )) >;

		/** Update cycle: Execute scheduled tasks using the calling thread.
			@warning This should only be called by the system managing this object (most of the time the Workspace), 
			in only one thread at a time.
		*/
		void update();

	protected:
		/** Base constructor.
			@param workspace		Workspace this object will be managed by.
			@param new_id			Unique id of the object. Have to be valid.
		*/
		explicit WorkspaceObject( Workspace& workspace, Id<T> new_id )
			: m_workspace( workspace )
			, m_id( std::move(new_id) )
		{
			if( !is_valid(m_id) )
			{
				std::stringstream error_message;
				error_message << "Tried to build a '" << typeid(T).name() << '\''
				<< " (inheriting from WorkspaceObject<" << typeid(T).name() << '>'
				<< " with an invalid ID : " << to_string(m_id);
				throw std::invalid_argument( error_message.str() );
			}
		}

		virtual ~WorkspaceObject(){} // = default;

		/** Add a task to be executed on the next object's update cycle and request an update.
			@remark If no update cycle is scheduled, calling this will request/trigger one.
			@param task				Callable object which takes no argument.
			@return The result of the task once executed.
		*/
		template< class TaskType >
		auto schedule( TaskType&& task ) -> future< decltype(task()) >;

		/** Execute a task asynchronously by using the Workspace's executor.
			@remark The task will not be executed in sync with this object's update.
			@param task				Callable object which takes no argument.
			@return The result of the task once executed.
		*/
		template< class TaskType >
		auto async( TaskType&& task ) -> future< decltype(task()) >;
		
		/** Publish an event.
			The event will be pushed into the Workspace's EventQueueDispatcher with this
			object id as being the source.
		*/
		template< class EventType >
		void publish( EventType&& e );
		
	private:
		WorkspaceObject( const WorkspaceObject& ); // = delete;
		WorkspaceObject& operator=( const WorkspaceObject& ); // = delete;

		mutable WorkQueue<void> m_work_queue;
		const Id<T> m_id;
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
	auto WorkspaceObject<T>::on_next_update( TaskType task ) -> future< decltype(task( *dummy() )) >
	{
		return schedule( [this,task]{
			return task( *static_cast<T*>(this) );
		});
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
	void WorkspaceObject<T>::update()
	{ 
		m_work_queue.execute();
		if( !m_work_queue.empty() )
			m_workspace.request_update();
	}


	template< class T >
	template< class EventType >
	void WorkspaceObject<T>::publish( EventType&& ev )
	{
		m_workspace.m_event_dispatcher.publish( id(), std::forward<EventType>(ev) );
	}


}}

#endif
#include <aosdesigner/backend/workspace.hpp>

#include <utilcpp/make_unique.hpp>

#include <atomic>

#include <aosdesigner/backend/tools/workqueue.hpp>

namespace aosd {
namespace backend {

	Workspace::Workspace( TaskExecutor executor )
		: m_executor( std::move(executor) )
		, pimpl( std::make_unique<Impl>( *this ) )
	{

	}

	Workspace::~Workspace()
	{

	}

	void Workspace::dispatch_events()
	{
		m_event_dispatcher.dispatch();
	}

	class Workspace::Impl
	{
	public:
		Impl( Workspace& workspace );

		void request_update();


	private:
		Workspace& m_workspace;

		WorkQueue<void> m_work_queue;
		std::atomic<unsigned long> m_update_request_count;

		void update_loop();
		void update();

	};

	void Workspace::request_update()
	{
		pimpl->request_update();
	}

	Workspace::Impl::Impl( Workspace& workspace ) 
		: m_workspace( workspace )
		, m_update_request_count( 0 )
	{

	}

	void Workspace::Impl::request_update()
	{
		if( m_update_request_count > 0 )
		{
			++m_update_request_count;
		}
		else
		{
			m_workspace.async( [&]{ update_loop(); } );
		}
	}

	void Workspace::Impl::update_loop()
	{
		++m_update_request_count;
		while( m_update_request_count > 0 )
		{
			const auto request_count_on_begin = m_update_request_count.load();
			update();
			m_update_request_count -= request_count_on_begin;			
		}
	}

	void Workspace::Impl::update()
	{
		m_work_queue.execute();
		if( !m_work_queue.empty() )
			request_update();

		// TODO: update all projects using async()

	}

	

}}
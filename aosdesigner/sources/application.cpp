#include "application.hpp"

#include "utilcpp/assert.hpp"
#include "utilcpp/log.hpp"

#include "core/context.hpp"
#include "view/applicationview.hpp"
#include "view/dialogs.hpp"

namespace aosd
{
	Application::Application( int &argc, char **argv )
		: m_context( new backend::Context() )
		, m_view( new view::ApplicationView( argc, argv ) )
	{
		UTILCPP_LOG << "New AOS Designer session start!";
		
		

		// TODO : add version informations to logs 
	}

	Application::~Application()
	{
		UTILCPP_LOG << "End of AOS Designer session!\nGood Bye!";
	}

	int Application::run()
	{
		return m_view->run( [&](){ start(); } );
	}

	void Application::exit()
	{
		UTILCPP_LOG << "Exiting...";
		m_view->exit();
	}

	void Application::start()
	{
		// TODO : start the state machine here
		view::show_welcome_screen();
	}


}
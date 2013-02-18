#include "Application.hpp"

#include "utilcpp/Assert.hpp"
#include "utilcpp/Log.hpp"

#include "core/Context.hpp"
#include "view/ApplicationView.hpp"
#include "view/Dialogs.hpp"

namespace aosd
{
	Application::Application( int &argc, char **argv )
		: m_context( new core::Context() )
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
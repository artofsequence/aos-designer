#ifndef HGUARD_AOSD_APPLICATION_HPP__
#define HGUARD_AOSD_APPLICATION_HPP__
#pragma once

#include <memory>
#include "utilcpp/Singleton.hpp"

namespace aosd
{
	namespace core { class Context; }
	namespace view { class ApplicationView; }

	/** Root object of this application.
	**/
	class Application
		: public util::Singleton<Application>
	{
	public:

		Application( int &argc, char **argv );
		~Application();

		int run();
		void exit();

	private:

		
		/// Current context informations of the application : opened project, opened sequence, etc.
		std::unique_ptr<core::Context> m_context;
		
		/// Application view.
		std::unique_ptr<view::ApplicationView> m_view;


		void start();
		
	};


}


#endif

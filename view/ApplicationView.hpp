#ifndef HGUARD_AOSD_VIEW_APPLICATIONVIEW_HPP__
#define HGUARD_AOSD_VIEW_APPLICATIONVIEW_HPP__
#pragma once

#include <memory>
#include <functional>
#include <QApplication>

namespace aosd
{
namespace view
{
	class MainWindow;

	/** Application view, provided to Qt to be run and managing the whole state.
	**/
	class ApplicationView
		: public QApplication
	{
		Q_OBJECT
	public:

		typedef std::function< void () > Callback;

		ApplicationView( int &argc, char **argv );
		~ApplicationView();


		int run( Callback callback_on_ready );

		void show_main_window();

		
	private slots:

		void on_ready();

	private:

		/// Window of the application.
		std::unique_ptr<MainWindow> m_main_window;
		
		Callback m_on_ready;

		
	};

}
}


#endif

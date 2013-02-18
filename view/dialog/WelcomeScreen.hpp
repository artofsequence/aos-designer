#ifndef HGUARD_AOSD_WELCOMESCREEN_HPP__
#define HGUARD_AOSD_WELCOMESCREEN_HPP__
#pragma once

#include <memory>
#include <QDialog>

namespace Ui { class WelcomeScreen; }

namespace aosd
{
namespace view
{
	/** Screen displayed when opening the application.
		Offer basic choices of actions like create a new project or open a project.
	*/
	class WelcomeScreen
		: public QDialog
	{
		Q_OBJECT
	public:

		WelcomeScreen();
		~WelcomeScreen();
	

	private:

		/** UI file defining the window look. */
		std::unique_ptr<Ui::WelcomeScreen> m_ui;

		
	};
}
}


#endif
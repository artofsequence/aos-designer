#include "WelcomeScreen.hpp"

#include <QImage>
#include "ui_WelcomeScreen.h"

#include "utilcpp/Assert.hpp"
#include "core/Context.hpp"

namespace aosd
{
namespace view
{

	WelcomeScreen::WelcomeScreen()
		: m_ui( new Ui::WelcomeScreen() )
	{
		m_ui->setupUi( this );
		m_ui->logo_display->setPixmap( QPixmap::fromImage( QImage( ":/images/welcome_logo" ) ) );

		auto* context = &core::Context::instance();
		UTILCPP_ASSERT_NOT_NULL( context );

		// connect the buttons to the actions
		connect( m_ui->button_new_project, SIGNAL(clicked()), context, SLOT(new_project()) );
		connect( m_ui->button_open_project, SIGNAL(clicked()), context, SLOT(open_project()) );

		// once we have an open project, just close this screen
		connect( context, SIGNAL(project_open(const core::Project&)), this, SLOT(close()) );
	}

	WelcomeScreen::~WelcomeScreen()
	{

	}

}
}
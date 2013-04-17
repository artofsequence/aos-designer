#include "logview.hpp"

#include <QTextEdit>
#include <QScrollBar>


namespace aosd
{

namespace view
{

	LogView::LogView()
		: m_text_area( new QTextEdit() )
	{
#ifdef _DEBUG
		setVisible( true );
#else
		setVisible( false );
#endif

		setWindowTitle(tr("Log"));
		setWidget( m_text_area.get() );

		m_text_area->setReadOnly(true);
		
		util::register_log_output( [&]( util::Log::Level level, const std::string& message ){ print_log( level, message ); }, 1 );

	}

	LogView::~LogView()
	{
		util::unregister_log_output( 1 );
	}

	void LogView::print_log( util::Log::Level level, const std::string& message )
	{
		auto color = level < util::Log::INFO ? "red" : "black";

		auto display_message = QString("<br /><font color=\"%1\" >%2</font>" ).arg( color, 1 ).arg( QString::fromStdString( message ), 2 );


		m_text_area->insertHtml( display_message );
		m_text_area->verticalScrollBar()->setSliderPosition( m_text_area->verticalScrollBar()->maximum() );
	}

}

}
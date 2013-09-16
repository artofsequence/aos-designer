#ifndef HGUARD_AOSD_VIEW_LOGVIEW_HPP__
#define HGUARD_AOSD_VIEW_LOGVIEW_HPP__
#pragma once

#include <memory>
#include <QDockWidget>
#include <QListView>

#include <utilcpp/log.hpp>


class QTextEdit;

namespace aosd
{
namespace view
{
	/** Display the logs of activity of the application. 
	**/
	class LogView
		: public QDockWidget
	{
		Q_OBJECT
	public:

		LogView();
		~LogView();


	private:

		std::unique_ptr<QTextEdit> m_text_area;

		void print_log( util::Log::Level level, const std::string& message );


	};


}
}

#endif

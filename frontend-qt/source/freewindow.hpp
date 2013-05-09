#ifndef HGUARD_AOSD_VIEW_FREEWINDOW_HPP__
#define HGUARD_AOSD_VIEW_FREEWINDOW_HPP__
#pragma once

#include <memory>
#include <QObject>

class QWidget;
class QAction;
class QMdiSubWindow;
class QMdiArea;
class QSplitter;
class QToolBar;

namespace aosd
{
namespace view
{

	/** Window that can automatically switch from inside an MDI area to outside it.
	**/
	class FreeWindow
		: public QObject
	{
		Q_OBJECT
		
	public:

		explicit FreeWindow( QWidget& widget, QMdiArea& window_area );
		~FreeWindow();

		QMdiSubWindow& window() { return *m_window; }

		void go_inside();
		void go_outside();

		bool is_inside() const { return m_is_inside; }

	private slots:

		void react_get_inside();
		void react_get_outside();
		
	private:

		QWidget& m_widget;
		QMdiArea& m_window_area;

		bool m_is_inside;

		std::unique_ptr<QMdiSubWindow> m_window;
		std::unique_ptr<QToolBar> m_toolbar;
		std::unique_ptr<QSplitter> m_splitter;

		std::unique_ptr<QAction> m_float_action;
		std::unique_ptr<QAction> m_dock_action;

		void initialize_inside_window();
		void terminate_inside_window();

		void initialize_outside_window();
		void terminate_outside_window();

	};

}
}


#endif

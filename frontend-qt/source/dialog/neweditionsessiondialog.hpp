#ifndef HGUARD_AOSD_VIEW_NEWEDITORDIALOG_HPP__
#define HGUARD_AOSD_VIEW_NEWEDITORDIALOG_HPP__
#pragma once

#include <memory>
#include <QDialog>
#include <aosdesigner/backend/editionsessioninfo.hpp>

namespace Ui
{
	class NewEditorDialog;
}

namespace aosd
{
namespace view
{
	/** Dialog used to ask the user details on a new sequence to create. */
	class NewEditorDialog
		: public QDialog
	{
		Q_OBJECT;
	public:

		NewEditorDialog();
		~NewEditorDialog();

	public slots:

		backend::EditorInfo info() const;

	private slots:

		void create_session();
		void update_name();
			
	private:

		std::unique_ptr< Ui::NewEditorDialog > m_ui;

		
		void fill_editor_selector();
	};

}
}


#endif

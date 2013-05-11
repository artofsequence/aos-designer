#ifndef HGUARD_AOSD_VIEW_NEWEDITIONSESSIONDIALOG_HPP__
#define HGUARD_AOSD_VIEW_NEWEDITIONSESSIONDIALOG_HPP__
#pragma once

#include <memory>
#include <QDialog>
#include <aosdesigner/backend/editionsessioninfos.hpp>

namespace Ui
{
	class NewEditionSessionDialog;
}

namespace aosd
{
namespace view
{
	/** Dialog used to ask the user details on a new sequence to create. */
	class NewEditionSessionDialog
		: public QDialog
	{
		Q_OBJECT;
	public:

		NewEditionSessionDialog();
		~NewEditionSessionDialog();

	public slots:

		backend::EditionSessionInfos infos() const;

	private slots:

		void create_session();
		void update_name();
			
	private:

		std::unique_ptr< Ui::NewEditionSessionDialog > m_ui;

		
		void fill_session_selector();
	};

}
}


#endif

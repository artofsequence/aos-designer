#ifndef HGUARD_AOSD_VIEW_NEWPROJECTDIALOG_HPP__
#define HGUARD_AOSD_VIEW_NEWPROJECTDIALOG_HPP__
#pragma once

#include <memory>
#include <QDialog>

#include <aosdesigner/backend/projectinfo.hpp>

namespace Ui { class NewProjectDialog; }

namespace aosd
{
namespace view
{
	/** Dialog used to ask the user details on a new project to create.
	*/
	class NewProjectDialog
		: public QDialog
	{
		Q_OBJECT;
	public:

		NewProjectDialog();
		~NewProjectDialog();

		/** Provide the basic information about the project described by the user. */
		backend::ProjectInfo info();

	private slots:

		
		void find_location();
		void create_project();
		void update_codename();
		void update_project_file();

	
	private:

		std::unique_ptr< Ui::NewProjectDialog > m_ui;

		
	};
}
}


#endif
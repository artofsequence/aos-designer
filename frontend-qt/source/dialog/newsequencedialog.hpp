#ifndef HGUARD_AOSD_VIEW_NEWSEQUENCEDIALOG_HPP__
#define HGUARD_AOSD_VIEW_NEWSEQUENCEDIALOG_HPP__
#pragma once

#include <memory>
#include <QDialog>

#include "core/sequenceinfos.hpp"

namespace Ui { class NewSequenceDialog; }

namespace aosd
{
namespace view
{
	/** Dialog used to ask the user details on a new sequence to create.
	*/
	class NewSequenceDialog
		: public QDialog
	{
		Q_OBJECT;
	public:

		NewSequenceDialog();
		~NewSequenceDialog();

		/** Provide the basic informations about the sequence described by the user. */
		backend::SequenceInfos infos();

	private slots:

		void create_sequence();
		void update_codename();
			
	private:

		std::unique_ptr< Ui::NewSequenceDialog > m_ui;

		
	};
}
}


#endif
#ifndef HGUARD_AOSD_VIEW_SEQUENCELISTVIEW_HPP__
#define HGUARD_AOSD_VIEW_SEQUENCELISTVIEW_HPP__
#pragma once

#include <utility>

#include <QListView>
#include <QStringListModel>

class QListView;

namespace aosd
{
namespace core
{
	class Project;
	class Sequence;
}
namespace view
{

	/** Display a list of Sequences in the currently open project.
		Allows editing, opening, closing and selecting sequences.
	*/
	class SequenceListView
		: public QListView
	{
		Q_OBJECT
	public:
		
		/** Constructor. */
		SequenceListView();

	private slots:

		void react_project_open( const core::Project& );
		void react_project_closed( const core::Project& );

		void react_sequence_created( const core::Sequence& );
		void react_sequence_deleted( const core::Sequence& );

	private:

		QStringListModel m_string_list;

		/** Read the Sequences in the provided project and retrieve their data
			to be displayed in this widget.
		*/
		void read_sequences( const core::Project& project );

		/** Clear the displayed infos. */
		void clear();

		void connect_context();
		void connect_project( const core::Project& project );
		void disconnect_project( const core::Project& project );

		void add_sequence_infos( const core::Sequence& sequence );
		void remove_sequence_infos( const core::Sequence& sequence );

	};



}
}


#endif

#include "view/sequencelistview.hpp"

#include <QListView>

#include "utilcpp/assert.hpp"

#include "core/context.hpp"
#include "core/project.hpp"
#include "core/sequence.hpp"

namespace aosd
{
namespace view
{

	SequenceListView::SequenceListView()
	{
		// configure the list
		setWindowTitle(tr("Sequences"));
		setSelectionMode( QAbstractItemView::SingleSelection );
		setEditTriggers( QAbstractItemView::NoEditTriggers ); // TODO : allow edition but then report the Sequence name change in the Project.Sequence.
		
		// the model informations
		setModel( &m_string_list );

		// connect to context signals
		connect_context();
		
	}


	void SequenceListView::connect_context()
	{
		auto& context = core::Context::instance();
		connect( &context, SIGNAL( project_open(const core::Project&)    ) , this, SLOT( react_project_open(const core::Project&)       ) );
		connect( &context, SIGNAL( project_closed(const core::Project&)  ) , this, SLOT( react_project_closed(const core::Project&)     ) );

		if( context.is_project_open() )
		{
			connect_project( context.current_project() );
		}
		

	}

	void SequenceListView::connect_project( const core::Project& project )
	{
		connect( &project, SIGNAL( sequence_created(const core::Sequence&)    ) , this, SLOT( react_sequence_created(const core::Sequence&)       ) );
		connect( &project, SIGNAL( sequence_deleted(const core::Sequence&)    ) , this, SLOT( react_sequence_deleted(const core::Sequence&)       ) );


		read_sequences( project );
	}

	void SequenceListView::disconnect_project( const core::Project& project )
	{
		disconnect( &project, 0, this, 0 );
		clear();
	}


	void SequenceListView::add_sequence_infos( const core::Sequence& sequence )
	{
		auto sequences_infos = m_string_list.stringList();
		sequences_infos << QString::fromStdString( sequence.name() );

		m_string_list.setStringList( sequences_infos );
	}


	void SequenceListView::remove_sequence_infos( const core::Sequence& sequence )
	{
		auto sequences_infos = m_string_list.stringList();
		sequences_infos.removeAt( sequences_infos.lastIndexOf( QString::fromStdString( sequence.name() ) ) );

		m_string_list.setStringList( sequences_infos );
	}



	void SequenceListView::read_sequences( const core::Project& project )
	{
		QStringList sequences_infos;
		
		project.foreach_sequence( [&]( const core::Sequence& sequence )
		{
			sequences_infos << QString::fromStdString( sequence.name() );
		});

		m_string_list.setStringList( sequences_infos );
	}

	void SequenceListView::clear()
	{
		m_string_list.setStringList(QStringList()); 
	}


	void SequenceListView::react_project_open( const core::Project& project )
	{
		connect_project( project );
	}

	void SequenceListView::react_project_closed( const core::Project& project )
	{
		disconnect_project( project );
	}


	void SequenceListView::react_sequence_created( const core::Sequence& sequence )
	{
		add_sequence_infos( sequence );
	}

	void SequenceListView::react_sequence_deleted( const core::Sequence& sequence )
	{
		remove_sequence_infos( sequence );
	}



}
}
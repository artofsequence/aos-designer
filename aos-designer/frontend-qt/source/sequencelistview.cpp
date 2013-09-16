#include "sequencelistview.hpp"

#include <QListView>

#include <utilcpp/assert.hpp>

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/sequence.hpp>

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
		
		// the model information
		setModel( &m_string_list );

		// connect to context signals
		connect_context();
		
	}


	void SequenceListView::connect_context()
	{
		auto& context = backend::Context::instance();
		connect( &context, SIGNAL( project_open(const backend::Project&)    ) , this, SLOT( react_project_open(const backend::Project&)       ) );
		connect( &context, SIGNAL( project_closed(const backend::Project&)  ) , this, SLOT( react_project_closed(const backend::Project&)     ) );

		if( context.is_project_open() )
		{
			connect_project( context.current_project() );
		}
		

	}

	void SequenceListView::connect_project( const backend::Project& project )
	{
		connect( &project, SIGNAL( sequence_created(const backend::Sequence&)    ) , this, SLOT( react_sequence_created(const backend::Sequence&)       ) );
		connect( &project, SIGNAL( sequence_deleted(const backend::Sequence&)    ) , this, SLOT( react_sequence_deleted(const backend::Sequence&)       ) );


		read_sequences( project );
	}

	void SequenceListView::disconnect_project( const backend::Project& project )
	{
		disconnect( &project, 0, this, 0 );
		clear();
	}


	void SequenceListView::add_sequence_info( const backend::Sequence& sequence )
	{
		auto sequences_info = m_string_list.stringList();
		sequences_info << QString::fromStdString( sequence.name() );

		m_string_list.setStringList( sequences_info );
	}


	void SequenceListView::remove_sequence_info( const backend::Sequence& sequence )
	{
		auto sequences_info = m_string_list.stringList();
		sequences_info.removeAt( sequences_info.lastIndexOf( QString::fromStdString( sequence.name() ) ) );

		m_string_list.setStringList( sequences_info );
	}



	void SequenceListView::read_sequences( const backend::Project& project )
	{
		QStringList sequences_info;
		
		project.foreach_sequence( [&]( const backend::Sequence& sequence )
		{
			sequences_info << QString::fromStdString( sequence.name() );
		});

		m_string_list.setStringList( sequences_info );
	}

	void SequenceListView::clear()
	{
		m_string_list.setStringList(QStringList()); 
	}


	void SequenceListView::react_project_open( const backend::Project& project )
	{
		connect_project( project );
	}

	void SequenceListView::react_project_closed( const backend::Project& project )
	{
		disconnect_project( project );
	}


	void SequenceListView::react_sequence_created( const backend::Sequence& sequence )
	{
		add_sequence_info( sequence );
	}

	void SequenceListView::react_sequence_deleted( const backend::Sequence& sequence )
	{
		remove_sequence_info( sequence );
	}



}
}
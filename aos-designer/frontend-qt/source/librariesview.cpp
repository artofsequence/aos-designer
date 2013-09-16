#include "librariesview.hpp"

#include <QSplitter>
#include <QTreeView>

#include <aosdesigner/backend/context.hpp>
#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include "model/librarymodel.hpp"

namespace aosd
{
namespace view
{

	LibrariesView::LibrariesView()
		: m_splitter( new QSplitter )
		, m_project_library_view( new QTreeView )
		, m_sequence_library_view( new QTreeView )
		, m_project_library_model( new LibraryModel )
		, m_sequence_model_view_binder( *m_sequence_library_view )
	{
		setWindowTitle( tr("Libraries") );
		m_sequence_library_view->setWindowTitle( tr( "Sequence Library" ) );
		m_project_library_view->setWindowTitle( tr( "Project Library" ) );


		m_project_library_view->setModel( m_project_library_model.get() );

		m_splitter->setOrientation( Qt::Vertical );
		m_splitter->addWidget( m_sequence_library_view.get() );
		m_splitter->addWidget( m_project_library_view.get() );
		setWidget( m_splitter.get() );
	}

	void LibrariesView::connect_edition( const backend::Editor& editor )
	{
		if( m_sequence_model_view_binder.current_id() != editor.sequence_id() )
		{
			m_sequence_model_view_binder.load( editor.sequence_id() );
		}
	}

	void LibrariesView::disconnect_edition( const backend::Editor& editor )
	{
		m_sequence_model_view_binder.unload();
	}

	void LibrariesView::connect_project( const backend::Project& project )
	{
		m_project_library_model->update( project.library() );

		project.foreach_sequence( [&](const backend::Sequence& sequence )
		{
			add_sequence_library( sequence );
		});
	}

	void LibrariesView::disconnect_project( const backend::Project& project )
	{
		m_project_library_model->clear();
		m_sequence_model_view_binder.clear();
	}

	void LibrariesView::begin_editor( const backend::Editor& editor )
	{
		if( m_sequence_model_view_binder.find( editor.sequence_id() ) == nullptr )
		{
			auto sequence = backend::Context::instance().current_project().find_sequence( editor.sequence_id() );

			UTILCPP_ASSERT_NOT_NULL( sequence );
			UTILCPP_ASSERT( sequence->id() == editor.sequence_id(), "Sequence found with an id doesn't contain the same Id???? "
				<<	" Find id : " << editor.sequence_id()
				<<  " Got id : " << sequence->id() 
				);

			add_sequence_library( *sequence );
		}
		

	}

	void LibrariesView::end_editor( const backend::Editor& editor )
	{
		const auto& project = backend::Context::instance().current_project();

		bool no_more_edition_for_this_sequence = true;

		project.foreach_edition( [&]( const backend::Editor& other_session )
		{
			if(	&other_session != &editor
			&&	other_session.sequence_id() == editor.sequence_id() 
			)
			{
				no_more_edition_for_this_sequence = false;
			}
		});

		if( no_more_edition_for_this_sequence )
			m_sequence_model_view_binder.remove( editor.sequence_id() );
	}

	void LibrariesView::add_sequence_library( const backend::Sequence& sequence )
	{
		auto model = std::unique_ptr<LibraryModel>( new LibraryModel() );
		model->update( sequence.library() );

		m_sequence_model_view_binder.add( std::move(model), sequence.id() );
		m_sequence_model_view_binder.load( sequence.id() );
	}


}

}
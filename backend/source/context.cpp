#include <aosdesigner/backend/context.hpp>

#include <boost/exception/diagnostic_information.hpp>

#include <utilcpp/assert.hpp>

#include <aosdesigner/backend/project.hpp>
#include <aosdesigner/backend/sequence.hpp>
#include <aosdesigner/backend/editor.hpp>
#include <aosdesigner/backend/paths.hpp>
#include <aosdesigner/backend/projectinfo.hpp>

namespace aosd
{
namespace backend
{


	Context::Context()
		: m_project( nullptr )
	{

	}


	Context::~Context()
	{

	}
	
	bool Context::new_project( const ProjectInfo& info )
	{
		UTILCPP_ASSERT( is_valid( info ), "Tried to create a new project with invalid information!" );
		
		std::unique_ptr<Project> project( new Project( *this, info ) );
		project->save();			// save everything

		const bool project_open = open_project( std::move(project) );
		if( !project_open )
			return false;

		UTILCPP_ASSERT_NOT_NULL( m_project );

		
		return true;
	}

	// TODO: FIXME
	//bool Context::open_project()
	//{
	//	auto project_file_path = view::request_project_path();

	//	if( project_file_path.empty() 
	//	||  !( project_file_path.extension() == path::PROJECT_FILE_EXTENSION )
	//	)
	//	{
	//		return false; // THINK : do something else if it failed?
	//	}

	//	if( is_project_open() ) 
	//		close_project(); // TODO : don't continue if the close failed!
	//	
	//	return open_project( std::unique_ptr<Project>( new Project( project_file_path ) ) );
	//}

	bool Context::open_project( std::unique_ptr<Project> project )
	{
		UTILCPP_ASSERT_NOT_NULL( project );

		if( is_project_open() )
			close_project();

		m_project.swap( std::move( project ) );

		/* TODO: emit */ project_open( current_project() );
		return true;
	}

	void Context::close_project()
	{
		if( is_project_open() )
		{
			m_project->close();
			/* TODO: emit */ project_closed( *m_project );
			m_project.reset();
		}
		
	}

	bool Context::is_project_open() const
	{
		return m_project;
	}

	const Project& Context::current_project() const
	{
		return *m_project;
	}
	

	bool Context::new_edition( const EditorInfo& editor_info )
	{
		if( is_project_open() )
		{
			return m_project->new_edition( editor_info );
		}

		// THINK : replace that with an exception?
		UTILCPP_LOG_ERROR << "Cannot create a editor while no project is open!";

		return false;
	}


	bool Context::save_project()
	{
		if( is_project_open() )
		{
			return m_project->save();
		}

		// THINK : replace that with an exception?
		UTILCPP_LOG_ERROR << "Cannot save the project: no project is open!";

		return false;
	}

	bool Context::restore_project()
	{
		if( is_project_open() )
		{
			auto project_location = m_project->location();
			close_project();
			return open_project( std::unique_ptr<Project>( new Project( *this, project_location ) ) );
		}

		// THINK : replace that with an exception?
		UTILCPP_LOG_ERROR << "Cannot restore the project: no project is open!";

		return false;
	}

	void Context::select_editor( EditorId editor_id )
	{
		if( is_project_open() )
		{
			m_project->select_editor( editor_id );
		}
	}

	const Editor* Context::selected_editor() const
	{
		if( is_project_open() )
		{
			return m_project->selected_editor();
		}

		return nullptr;
	}

	bool Context::delete_edition( EditorId editor_id )
	{
		if( is_project_open() )
		{
			return m_project->delete_edition( editor_id );
		}
		return false;
	}


}
}
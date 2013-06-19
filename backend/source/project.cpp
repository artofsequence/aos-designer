#include <aosdesigner/backend/project.hpp>

#include <vector>
#include <boost/container/flat_map.hpp>

#include <utilcpp/assert.hpp>
#include <utilcpp/make_unique.hpp>

#include <aosdesigner/backend/editor.hpp>

namespace aosd {
namespace backend {


	using boost::container::flat_map;

	class Project::Impl
	{
	public:
		explicit Impl( Project& project, ProjectInfo project_info );

		void add( std::shared_ptr<Editor> editor );
		void add( std::shared_ptr<Library> library );

		EditorId open_editor( EditorInfo info );
		
	private:
		Impl( const Impl& ); // = delete;
		Impl& operator=( const Impl& ); // = delete;

		Project& m_project;

		flat_map< Id<Library>, std::shared_ptr<Library> > m_library_index;
		flat_map< Id<Editor>, std::shared_ptr<Editor> > m_editor_index;
		
	};

	Project::Impl::Impl( Project& project, ProjectInfo project_info )
		: m_project( project )
	{

	}

	EditorId Project::Impl::open_editor( EditorInfo info )
	{

	}



	/////////////////////////////////////////////////////////


	Project::Project( Workspace& workspace, ProjectInfo info )
		: WorkspaceObject( workspace, info.id )
		, m_impl( std::make_unique<Impl>( *this, info ) )
	{

	}

	Project::~Project()
	{

	}

	aosd::backend::ProjectInfo Project::info() const
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return ProjectInfo();
	}


	future<void> Project::add_sequence( SequenceInfo info )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<void> Project::remove_sequence( SequenceId sequence_id )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<void> Project::add_library( LibraryInfo info )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<void> Project::remove_library( LibraryId library_id )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

	future<EditorId> Project::open_editor( EditorInfo info )
	{
		return schedule( [this,info]{ return m_impl->open_editor( info ); } );
	}

	future<void> Project::close_editor( EditorId editor_id )
	{
		UTILCPP_NOT_IMPLEMENTED_YET;
		return make_ready_future();
	}

}}
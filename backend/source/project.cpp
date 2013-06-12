#include <aosdesigner/backend/project.hpp>


#include <utilcpp/assert.hpp>
#include <utilcpp/make_unique.hpp>
#include <boost/container/flat_map.hpp>

namespace aosd {
namespace backend {

	class Project::Impl
	{
	public:
		
	private:

		boost::container::flat_map< Id<Library>, std::shared_ptr<Library> > m_library_index;
		boost::container::flat_map< Id<Editor>, std::shared_ptr<Editor> > m_editor_index;


	};


	//Project::Project( Workspace& workspace )
	//	: WorkspaceObject( workspace )
	//	, impl( std::make_unique<Impl>() )
	//{

	//}

	//Project::Project( Workspace& workspace, ProjectInfo info )
	//	: WorkspaceObject( workspace )		// TODO this
	//	, impl( std::make_unique<Impl>() )  // TODO and this should be changed to Project( workspace )
	//{

	//}

	//Project::~Project()
	//{

	//}

	//aosd::backend::ProjectInfo Project::info() const
	//{

	//}

	//future<void> Project::rename( std::string new_name )
	//{

	//}

	//future<void> Project::relocate( URI new_location )
	//{

	//}

	//future<SequenceId> Project::create_sequence()
	//{

	//}

	//future<void> Project::add_sequence( SequenceInfo info )
	//{

	//}

	//future<void> Project::remove_sequence( SequenceId sequence_id )
	//{

	//}

}}
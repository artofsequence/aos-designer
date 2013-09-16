#ifndef HGUARD_AOSD_BACKEND_PROJECTEVENTS_HPP__
#define HGUARD_AOSD_BACKEND_PROJECTEVENTS_HPP__

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/info/projectinfo.hpp>
#include <aosdesigner/backend/info/sequenceinfo.hpp>
#include <aosdesigner/backend/info/libraryinfo.hpp>

namespace aosd {
namespace backend {
namespace event {
	
	struct ProjectOpen						///< A Project have been opened for edition.
	{
		ProjectInfo		project_info;		///< Info of the open project.
	};

	struct ProjectClosed					///< An open Project have been closed.
	{
		ProjectId		project_id;			///< Id of the Project that have been closed.
	};

	struct SequenceAdded					///< A Sequence have been added to a Project.
	{
		ProjectId		project_id;			///< Id of the Project in which the Sequence was added.
		SequenceInfo	sequence_info;		///< Info of the added Sequence.
	};

	struct SequenceRemoved					///< A Sequence have been removed from a Project.
	{
		ProjectId		project_id;			///< Id of the project from which the Sequence have been removed.
		SequenceId		sequence_id;		///< Id of the Sequence removed from the Project.
	};

	struct ProjectLibraryAdded				///< A Library have been added to a Project, accessible to all it's Sequences.
	{
		ProjectId		project_id;			///< Id of the project in which the Library have been added.
		LibraryInfo		library_info;		///< Info of the added Library.
	};

	struct ProjectLibraryRemoved			///< A Library have been removed from a Project
	{
		ProjectId		project_id;			///< Id of the project from which the Library have been removed.
		LibraryId		library_id;			///< Id of the Library removed from the project.
	};

}}}

#endif

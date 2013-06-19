#ifndef HGUARD_AOSD_BACKEND_PROJECT_HPP__
#define HGUARD_AOSD_BACKEND_PROJECT_HPP__
#pragma once

#include <memory>
#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>
#include <aosdesigner/backend/projectinfo.hpp>
#include <aosdesigner/backend/sequenceinfo.hpp>
#include <aosdesigner/backend/editorinfo.hpp>
#include <aosdesigner/backend/libraryinfo.hpp>


namespace aosd { 
namespace backend {
		
	/** An open project, containing info about sequences, libraries and open editors.
		Destroying a Project instance closes it.
		@par
		Each project can contain:
		 - a set of sequences informations, which are associated with that project;
		 - a set of libraries which can be accessed by all the sequences in the project;
		 - a set of Editor instances, which are used to view and edit Sequence instances;
		@par
		Adding a sequence in the Project don't instantiate a Sequence object, 
		but opening an Editor of a sequence does (it needs to load the state of 
		the Sequence in memory and modify it accordingly).

		@remark The public member functions are all thread-safe.
		They return futures when the action will be done later 
		(usually on update, which is managed by the associated Workspace,
		@see WorkspaceObject ).
		They return by value or void when the action will be performed
		synchronously, which might imply waiting.
	*/
	class AOSD_BACKEND_API Project
		: public WorkspaceObject<Project>
	{
	public:
		explicit Project( Workspace& workspace, ProjectInfo info );
		~Project();

		ProjectInfo info() const;

		future<void> add_sequence( SequenceInfo info );
		future<void> remove_sequence( SequenceId sequence_id );

		future<void> add_library( LibraryInfo info );
		future<void> remove_library( LibraryId library_id );

		future<EditorId> open_editor( EditorInfo info );
		future<void> close_editor( EditorId editor_id );
		
	private:
		class Impl;
		std::unique_ptr<Impl> pimpl;

	};


}}


#endif


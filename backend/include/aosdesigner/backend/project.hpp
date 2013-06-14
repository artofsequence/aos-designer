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
		
	class AOSD_BACKEND_API Project
		: public WorkspaceObject<Project>
	{
	public:
		explicit Project( Workspace& workspace, ProjectInfo info );
		~Project();

		ProjectInfo info() const;

		future<void> rename( std::string new_name );
		future<void> relocate( URI new_location );
		
		future<void> add_sequence( SequenceInfo info );
		future<void> remove_sequence( SequenceId sequence_id );

		future<void> add_library( LibraryInfo info );
		future<void> remove_library( LibraryId library_id );

		future<std::shared_ptr<Editor>> open_editor( SequenceId sequence_id );
		future<void> close_editor( EditorId editor_id );
		
	private:
		class Impl;
		std::unique_ptr<Impl> impl;
	};


}}


#endif


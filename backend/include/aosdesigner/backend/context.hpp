#ifndef HGUARD_AOSD_BACKEND__CONTEXT_HPP__
#define HGUARD_AOSD_BACKEND__CONTEXT_HPP__
#pragma once
//
//#include <memory>
//
//#include <aosdesigner/backend/api.hpp>
//#include <aosdesigner/backend/id.hpp>
//#include <aosdesigner/backend/resourceprovider.hpp>
//
//namespace aosd
//{
//namespace backend
//{
//	class Project;
//	struct ProjectInfo;
//	class Sequence;
//	struct SequenceInfo;
//	class Editor;
//	struct EditorInfo;
//
//	/** TODO: MISSING DOCUMENTATION
//	*/
//	class AOSD_BACKEND_API Context
//	{
//	public:
//
//		Context();
//		~Context();
//		
//		/** @return True if there is a project open currently. */
//		bool is_project_open() const;
//
//		/** Current project open for edition. */
//		const Project& current_project() const;
//
//		/** Current selected editor or null if none or if there is no project open. */
//		const Editor* selected_editor() const;
//
//		ResourceProvider& resource_provider() { return m_resource_provider; }
//		
//
//	// public slots:
//
//		/** Create a new empty project using the provided information and set it as the current project.
//			If there was already a project open, it will be closed first.
//			@return false if the project creation process failed, true otherwise.
//		*/
//		bool new_project( const ProjectInfo& info );
//
//		/** Close the currently open project. */
//		void close_project();
//		
//		/** Open a project by asking it's location to the user. 
//			@return false if the project loading process failed or have been canceled by the user, true otherwise.
//		*/
//		// TODO: FIXME bool open_project();
//
//		/** Save the project and everything it contains. */
//		bool save_project();
//
//		/** Close the current project without saving it and load the last saved version of it. */
//		bool restore_project();
//
//		/** Create a new editor for a sequence of the project.
//			@param editor_info Information necessary to create a new editor.
//			@return false if the editor creation failed or if there is no project currently open, true otherwise.
//		**/
//		bool new_edition( const EditorInfo& editor_info );
//
//		/** Delete an editor of the current project.
//			@return false if the editor deletion failed or was canceled or if the editor was not found. 
//		**/
//		bool delete_edition( EditorId editor_id );
//
//		/** Select the referred editor. */
//		void select_editor( EditorId editor_id );
//		
//	// signals:
//
//		/** Signal : a project have been open. */
//		void project_open( const backend::Project& project );
//
//
//		/** Signal : the currently open project will be closed. */
//		void project_closed( const backend::Project& project );
//		
//	private:
//
//		ResourceProvider m_resource_provider;
//
//		/// The currently open project or null if none.
//		std::unique_ptr< Project > m_project;
//
//		/** Open a project that have been loaded. 
//			@return false if the project loading process failed or have been canceled by the user, true otherwise.
//		*/
//		bool open_project( std::unique_ptr<Project> project );
//
//	};
//
//

}
}


#endif

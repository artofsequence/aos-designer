#ifndef HGUARD_AOSD_CORE__CONTEXT_HPP__
#define HGUARD_AOSD_CORE__CONTEXT_HPP__
#pragma once

#include <memory>

#include <utilcpp/singleton.hpp>

#include <aosdesigner/backend/sequenceid.hpp>
#include <aosdesigner/backend/editionsessionid.hpp>
#include <aosdesigner/backend/resourceprovider.hpp>

namespace aosd
{
namespace core
{
	class Project;
	struct ProjectInfos;
	class Sequence;
	struct SequenceInfos;
	class EditionSession;
	struct EditionSessionInfos;

	/** Singleton that hold the current context of the application, 
		like the current project to work on and the open sequence.
	*/
	class Context
		: public util::Singleton< Context >
	{
	public:

		Context();
		~Context();
		
		/** @return True if there is a project open currently. */
		bool is_project_open() const;

		/** Current project open for edition. */
		const Project& current_project() const;

		/** Current selected edition session or null if none or if there is no project open. */
		const EditionSession* selected_edition_session() const;

		ResourceProvider& resource_provider() { return m_resource_provider; }
		

	// public slots:

		/** Create a new empty project by asking details to the user and set it as the current project.
			If there was already a project open, it will be closed first.
			@return false if the project creation process failed or have been canceled by the user, true otherwise.
		*/
		bool new_project();

		/** Create a new empty project using the provided informations and set it as the current project.
			If there was already a project open, it will be closed first.
			@return false if the project creation process failed, true otherwise.
		*/
		bool new_project( const ProjectInfos& infos );

		/** Close the currently open project. */
		void close_project();
		
		/** Open a project by asking it's location to the user. 
			@return false if the project loading process failed or have been canceled by the user, true otherwise.
		*/
		bool open_project();

		/** Save the project and everything it contains. */
		bool save_project();

		/** Close the current project without saving it and load the last saved version of it. */
		bool restore_project();

		/** Create a new sequence in the current project. 
			@return false if the sequence creation failed or if there is no project currently open, true otherwise.
		**/
		bool new_sequence();
		
		/** Create a new edition session for a sequence of the project.
			@param session_infos Informations necessary to create a new edition session.
			@return false if the edition session creation failed or if there is no project currently open, true otherwise.
		**/
		bool new_edition( const EditionSessionInfos& session_infos );

		/** Create a new edition session for a sequence of the project.
			@return false if the edition session creation failed or if there is no project currently open, true otherwise.
		**/
		bool new_edition();

		/** Delete an edition session of the current project.
			@return false if the edition session deletion failed or was canceled or if the edition session was not found. 
		**/
		bool delete_edition( EditionSessionId session_id );

		/** Select the referred edition session. */
		void select_edition_session( EditionSessionId session_id );
		
	// signals:

		/** Signal : a project have been open. */
		void project_open( const core::Project& project );


		/** Signal : the currently open project will be closed. */
		void project_closed( const core::Project& project );
		
	private:

		ResourceProvider m_resource_provider;

		/// The currently open project or null if none.
		std::unique_ptr< Project > m_project;

		/** Open a project that have been loaded. 
			@return false if the project loading process failed or have been canceled by the user, true otherwise.
		*/
		bool open_project( std::unique_ptr<Project> project );

	};



}
}


#endif

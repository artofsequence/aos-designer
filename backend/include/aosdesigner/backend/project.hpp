#ifndef HGUARD_AOSD_BACKEND_PROJECT_HPP__
#define HGUARD_AOSD_BACKEND_PROJECT_HPP__
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/sequenceid.hpp>
#include <aosdesigner/backend/editionsessionid.hpp>
#include <aosdesigner/backend/library.hpp>

namespace aosd 
{ 
namespace backend 
{
	class Context;
	class Sequence;
	class EditionSession;
	struct ProjectInfos;
	struct SequenceInfos;
	struct EditionSessionInfos;
	
	namespace bfs = boost::filesystem;

	/** Contains a set of Sequences and common informations applied to all those Sequences.

	*/
	class AOSD_BACKEND_API Project
	{
	public:
				
		/** Create a project from basic informations. */
		explicit Project( Context& context, const ProjectInfos& infos );

		/** Load a project from a provided project file location. */
		explicit Project( Context& context, const bfs::path& project_file_path );

		~Project();

		Context& context() const { return const_cast<Project&>(*this).m_context; }

		/// Path of the file that contain all the project's informations.
		bfs::path location() const { return m_location; }
		
		/// Path of the directory where this project's file is located.
		bfs::path directory_path() const { return m_directory_path; }

		/// Library containing resources available to all resources in this project.
		const Library& library() const { return m_library; }


		/** Name of the project. */
		std::string name() const { return m_name; }

		/** Call the provided function for each Sequence in this project but don't allow to modify them. */
		void foreach_sequence( std::function< void ( const Sequence& sequence )> func ) const;

		/** Call the provided function for each edition session in this project but don't allow to modify them. */
		void foreach_edition( std::function< void ( const EditionSession& edition )> func ) const;

		const Sequence* find_sequence( SequenceId sequence_id ) const {  return const_cast<Project*>(this)->find_sequence(sequence_id); }

		/** Current selected edition session or null if none or if there is no project open. */
		const EditionSession* selected_edition_session() const { return m_selected_session; }

		
	//public slots:

		/** Change the project's file location to the provided one. */
		void relocate( const bfs::path& new_filepath );

		/** Change the name of the project. */
		void rename( const std::string& new_name );

		/** Create a new "empty" sequence with provided informations. */
		bool new_sequence( const SequenceInfos& infos );
		
		/** Create an edition session for the referenced sequence. **/
		bool new_edition( const EditionSessionInfos& session_infos );

		/** Delete an edition session of the project. */
		bool delete_edition( EditionSessionId session_id );

		/** Select the referred edition session. */
		void select_edition_session( const EditionSessionId& session_id );

		/** Deselect the currently selected edition session if any. */
		void deselect_edition_session();

		/** Save the project informations and content in the provided location. */
		bool save( const bfs::path& filepath )
		{
			relocate(filepath);
			return save();
		}

		/** Save the project informations and content in the default location. */
		bool save();

		/** Close this project. */
		void close();

	// signals:

		/** Signal : a new sequence have been created. **/
		void sequence_created( const backend::Sequence& sequence );

		/** Signal : a sequence have been requested to be destroyed. **/
		void sequence_deleted( const backend::Sequence& sequence );

		/** Signal : at least one edition session is open now. */
		void edition_begin();

		/** Signal : no edition session is open now. */
		void edition_end();

		/** Signal : an edition session have been created. **/
		void edition_session_created( const backend::EditionSession& edition_session );
		
		/** Signal : an edition session have been deleted. **/
		void edition_session_deleted( const backend::EditionSession& edition_session );

		/** Signal : an edition session have began. **/
		void edition_session_begin( const backend::EditionSession& edition_session );

		/** Signal : an edition session will be ended. **/
		void edition_session_end( const backend::EditionSession& edition_session );

		/** Signal : an edition session have been selected. **/
		void edition_selected( const backend::EditionSession& edition_session );
		
		/** Signal : an edition session have been deselected. **/
		void edition_deselected( const backend::EditionSession& edition_session );

		
		
	private:
		Project( const Project& ); // = delete;
		Project& operator=( const Project& ); // = delete;

		Context& m_context;

		/// Sequences for this project.
		std::vector<std::unique_ptr< Sequence >> m_sequences;

		/// Sequence edition sessions.
		std::vector<std::unique_ptr< EditionSession >> m_edit_sessions;

		/// Name of the project.
		std::string m_name;
				
		/// Path of the file that contain all the project's informations about this project.
		bfs::path m_location;

		/// Path of the project's directory.
		bfs::path m_directory_path;

		/// Currently selected edition session.
		EditionSession* m_selected_session;

		/// Library containing resources available to all resources in this project.
		Library m_library;

		/// Add a Sequence to this project.
		void add_sequence( std::unique_ptr<Sequence> sequence );

		/// Add an edition session to this project.
		void add_edition( std::unique_ptr<EditionSession> sequence );

		/** Search for a Sequence having the provided id.
			@return The Sequence we looked after or null if not found. 
		**/
		Sequence* find_sequence( const SequenceId& sequence_id );

		/** Search for an edition session having the provided id.
		**/
		EditionSession* find_edition( EditionSessionId session_id );

	};

	

}
}


#endif


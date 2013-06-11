#ifndef HGUARD_AOSD_BACKEND_PROJECT_HPP__
#define HGUARD_AOSD_BACKEND_PROJECT_HPP__
#pragma once

#include <memory>
#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/projectinfo.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>

namespace aosd { 
namespace backend {
	
	class AOSD_BACKEND_API Project
		: public WorkspaceObject<Project>
	{
	public:
		explicit Project( Workspace& workspace );
		explicit Project( Workspace& workspace, ProjectInfo info );
		~Project();

		ProjectInfo info() const;

		future<void> rename( std::string new_name );
		future<void> relocate( URI new_location );
		
		future<SequenceId> create_sequence();
		future<void> add_sequence( SequenceInfo info );
		future<void> remove_sequence( SequenceId sequence_id );

		
	private:
		class Impl;
		std::unique_ptr<Impl> impl;
	};


	//class Context;
	//class Sequence;
	//class Editor;
	//struct ProjectInfo;
	//struct SequenceInfo;
	//struct EditorInfo;
	//
	//namespace bfs = boost::filesystem;

	///** Contains a set of Sequences and common information applied to all those Sequences.

	//*/
	//class AOSD_BACKEND_API Project
	//{
	//public:
	//			
	//	/** Create a project from basic information. */
	//	explicit Project( Context& context, const ProjectInfo& info );

	//	/** Load a project from a provided project file location. */
	//	explicit Project( Context& context, const bfs::path& project_file_path );

	//	~Project();

	//	Context& context() const { return const_cast<Project&>(*this).m_context; }

	//	/// Path of the file that contain all the project's information.
	//	bfs::path location() const { return m_location; }
	//	
	//	/// Path of the directory where this project's file is located.
	//	bfs::path directory_path() const { return m_directory_path; }

	//	/// Library containing resources available to all resources in this project.
	//	const Library& library() const { return m_library; }


	//	/** Name of the project. */
	//	std::string name() const { return m_name; }

	//	/** Call the provided function for each Sequence in this project but don't allow to modify them. */
	//	void foreach_sequence( std::function< void ( const Sequence& sequence )> func ) const;

	//	/** Call the provided function for each editor in this project but don't allow to modify them. */
	//	void foreach_edition( std::function< void ( const Editor& edition )> func ) const;

	//	const Sequence* find_sequence( SequenceId sequence_id ) const {  return const_cast<Project*>(this)->find_sequence(sequence_id); }

	//	/** Current selected editor or null if none or if there is no project open. */
	//	const Editor* selected_editor() const { return m_selected_session; }

	//	
	////public slots:

	//	/** Change the project's file location to the provided one. */
	//	void relocate( const bfs::path& new_filepath );

	//	/** Change the name of the project. */
	//	void rename( const std::string& new_name );

	//	/** Create a new "empty" sequence with provided information. */
	//	bool new_sequence( const SequenceInfo& info );
	//	
	//	/** Create an editor for the referenced sequence. **/
	//	bool new_edition( const EditorInfo& editor_info );

	//	/** Delete an editor of the project. */
	//	bool delete_edition( EditorId editor_id );

	//	/** Select the referred editor. */
	//	void select_editor( const EditorId& editor_id );

	//	/** Deselect the currently selected editor if any. */
	//	void deselect_editor();

	//	/** Save the project information and content in the provided location. */
	//	bool save( const bfs::path& filepath )
	//	{
	//		relocate(filepath);
	//		return save();
	//	}

	//	/** Save the project information and content in the default location. */
	//	bool save();

	//	/** Close this project. */
	//	void close();

	//// signals:

	//	/** Signal : a new sequence have been created. **/
	//	void sequence_created( const backend::Sequence& sequence );

	//	/** Signal : a sequence have been requested to be destroyed. **/
	//	void sequence_deleted( const backend::Sequence& sequence );

	//	/** Signal : at least one editor is open now. */
	//	void edition_begin();

	//	/** Signal : no editor is open now. */
	//	void edition_end();

	//	/** Signal : an editor have been created. **/
	//	void editor_created( const backend::Editor& editor );
	//	
	//	/** Signal : an editor have been deleted. **/
	//	void editor_deleted( const backend::Editor& editor );

	//	/** Signal : an editor have began. **/
	//	void editor_begin( const backend::Editor& editor );

	//	/** Signal : an editor will be ended. **/
	//	void editor_end( const backend::Editor& editor );

	//	/** Signal : an editor have been selected. **/
	//	void edition_selected( const backend::Editor& editor );
	//	
	//	/** Signal : an editor have been deselected. **/
	//	void edition_deselected( const backend::Editor& editor );

	//	
	//	
	//private:
	//	Project( const Project& ); // = delete;
	//	Project& operator=( const Project& ); // = delete;

	//	Context& m_context;

	//	/// Sequences for this project.
	//	std::vector<std::unique_ptr< Sequence >> m_sequences;

	//	/// Sequence edition sessions.
	//	std::vector<std::unique_ptr< Editor >> m_edit_sessions;

	//	/// Name of the project.
	//	std::string m_name;
	//			
	//	/// Path of the file that contain all the project's information about this project.
	//	bfs::path m_location;

	//	/// Path of the project's directory.
	//	bfs::path m_directory_path;

	//	/// Currently selected editor.
	//	Editor* m_selected_session;

	//	/// Library containing resources available to all resources in this project.
	//	Library m_library;

	//	/// Add a Sequence to this project.
	//	void add_sequence( std::unique_ptr<Sequence> sequence );

	//	/// Add an editor to this project.
	//	void add_edition( std::unique_ptr<Editor> sequence );

	//	/** Search for a Sequence having the provided id.
	//		@return The Sequence we looked after or null if not found. 
	//	**/
	//	Sequence* find_sequence( const SequenceId& sequence_id );

	//	/** Search for an editor having the provided id.
	//	**/
	//	Editor* find_edition( EditorId editor_id );

	//};

	//

}}


#endif


#ifndef HGUARD_AOSD_BACKEND_EDITOR_HPP__
#define HGUARD_AOSD_BACKEND_EDITOR_HPP__
#pragma once

#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>
#include <aosdesigner/backend/editorinfo.hpp>

namespace aosd {
namespace backend {

	class Project;

	class AOSD_BACKEND_API Editor
		: public WorkspaceObject<Editor>
	{
	public:
		~Editor();

		EditorInfo info() const;

	private:
		friend class Project;
		explicit Editor( Project& project );

		class Impl;
		std::unique_ptr<Impl> impl;

	};

	//class Project;
	//class Sequence;
	//

	//namespace bfs = boost::filesystem;

	///** Information about an editor of a sequence.
	//*/
	//class Editor
	//{
	//public:

	//	/** Constructor : create a new editor.
	//		@param project		Project in which this editor occurs.
	//		@param sequence		Sequence that is being walked in.
	//		@param name			Name of the session, displayed in views.
	//	**/
	//	Editor( const Project& project, const Sequence& sequence, const std::string& name );

	//	/**	Constructor : load a editor from a file.
	//		@param project		Project in which this session occurs.
	//		@param file_path	Path of the file containing the session information.
	//	**/
	//	Editor( const Project& project, const bfs::path& file_path );
	//
	//	EditorId id() const { return m_id; }
	//	SequenceId sequence_id() const { return m_sequence_id; }

	//	const std::string& name() const { return m_name; }
	//	const bfs::path& save_filepath() const { return m_save_filepath; }

	//	bool is_valid() const { return m_sequence && m_interpreter; }

	//	const aosl::Canvas& canvas() const { return m_interpreter->canvas().canvas(); }
	//	const aosl::Story& story() const { return m_interpreter->story(); }
	//	const aoslcpp::StoryPath& path() const { return m_interpreter->path(); }
	//	
	//// public slots:

	//	/** Save this editor state in a file at the provided path. */
	//	void save( const bfs::path& file_path );
	//
	//private:

	//	std::unique_ptr<aoslcpp::SequenceInterpreter> m_interpreter;

	//	std::string m_name;
	//	bfs::path m_save_filepath;

	//	const Project& m_project;
	//	const Sequence* m_sequence;

	//	EditorId m_id;
	//	SequenceId m_sequence_id;
	//};


}}


#endif
#ifndef HGUARD_AOSD_CORE_EDITIONSESSION_HPP__
#define HGUARD_AOSD_CORE_EDITIONSESSION_HPP__
#pragma once

#include <functional>
#include <boost/filesystem/path.hpp>
#include <qobject>

#include "core/sequenceid.hpp"
#include "core/editionsessionid.hpp"
#include "aoslcpp/sequenceinterpreter.hpp"
#include "aosl/aosl_forward.hpp"
#include "aoslcpp/algorithm/for_each.hpp"


namespace aosd
{
namespace core
{
	class Project;
	class Sequence;
	

	namespace bfs = boost::filesystem;

	/** Informations about an edition session of a sequence.
	*/
	class EditionSession
		: public QObject
	{
		Q_OBJECT
	public:

		/** Constructor : create a new edition session.
			@param project		Project in which this edition session occurs.
			@param sequence		Sequence that is being walked in.
			@param name			Name of the session, displayed in views.
		**/
		EditionSession( const Project& project, const Sequence& sequence, const std::string& name );

		/**	Constructor : load a edition session from a file.
			@param project		Project in which this session occurs.
			@param file_path	Path of the file containing the session informations.
		**/
		EditionSession( const Project& project, const bfs::path& file_path );
	
		EditionSessionId id() const { return m_id; }
		SequenceId sequence_id() const { return m_sequence_id; }

		const std::string& name() const { return m_name; }
		const bfs::path& save_filepath() const { return m_save_filepath; }

		bool is_valid() const { return m_sequence && m_interpreter; }

		const aosl::Canvas& canvas() const { return m_interpreter->canvas().canvas(); }
		const aosl::Story& story() const { return m_interpreter->story(); }
		const aoslcpp::StoryPath& path() const { return m_interpreter->path(); }
		
	public slots:

		/** Save this edition session state in a file at the provided path. */
		void save( const bfs::path& file_path );
		

	signals:

		
	private slots:


	private:

		std::unique_ptr<aoslcpp::SequenceInterpreter> m_interpreter;

		std::string m_name;
		bfs::path m_save_filepath;

		const Project& m_project;
		const Sequence* m_sequence;

		EditionSessionId m_id;
		SequenceId m_sequence_id;
	};


}
}


#endif
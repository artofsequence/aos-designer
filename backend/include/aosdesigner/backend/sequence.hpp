#ifndef HGUARD_AOSD_BACKEND_SEQUENCE_HPP__
#define HGUARD_AOSD_BACKEND_SEQUENCE_HPP__
#pragma once

#include <memory>

#include <aosdesigner/backend/api.hpp>
#include <aosdesigner/backend/id.hpp>
#include <aosdesigner/backend/sequenceinfo.hpp>
#include <aosdesigner/backend/workspaceobject.hpp>


namespace aosd {
namespace backend {

	class AOSD_BACKEND_API Sequence
		: public WorkspaceObject<Sequence>
	{
	public:

		explicit Sequence( Workspace& workspace );
		explicit Sequence( Workspace& workspace, SequenceInfo info );
		~Sequence();

		SequenceInfo info() const;
		aosl::Sequence aosl_model() const;


	private:

		class Impl;
		std::unique_ptr<Impl> impl;

	};

	//class AOSD_BACKEND_API Sequence
	//{
	//public:

	//	/** Create a new sequence using the provided information.
	//		@param project		Project in which this sequence exists.
	//		@param info		Information required to build the sequence.
	//	*/
	//	Sequence( const Project& project, const SequenceInfo& info );

	//	/** Create the sequence by loading information from the AOSL file at the the provided path.
	//		The path have to be 
	//	*/
	//	Sequence( const Project& project, boost::filesystem::path sequence_file_path );

	//	~Sequence();
	//	
	//	bool save();
	//	
	//	/// Name of the Sequence.
	//	const std::string& name() const { return m_name; }

	//	/// Unique identifier of this Sequence.
	//	SequenceId id() const { return m_id; }

	//	boost::filesystem::path location() const { return m_location; }
	//	boost::filesystem::path full_location() const;
	//	
	//	/// Project in which this sequence is loaded.
	//	const Project& project() const { return m_project; }
	//	
	//	/** Create an interpreter for this Sequence. */
	//	std::unique_ptr<aoslcpp::SequenceInterpreter> make_interpreter() const;

	//	/** Library for this Sequence. **/
	//	const Library& library() const { return m_library; }

	//private:

	//	/// Name of this Sequence
	//	std::string m_name;

	//	/// Unique identifier of this Sequence
	//	SequenceId m_id;

	//	/// Path relative to the project's folder of the file containing this sequence.
	//	boost::filesystem::path m_location;

	//	/// Expanded library specific to this sequence.
	//	Library m_library;

	//	/// Raw Sequence data.
	//	std::unique_ptr< aosl::Sequence > m_sequence;

	//	/// Project in which this sequence is loaded.
	//	const Project& m_project;

	//	
	//};



}}


#endif

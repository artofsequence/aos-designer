#ifndef HGUARD_AOSLCPP_EDITION_HPP__
#define HGUARD_AOSLCPP_EDITION_HPP__
#pragma once

#include <memory>
#include <string>

#include "aosl/aosl_forward.hpp"

namespace aoslcpp
{

	/// Prefix used in a unique id generated for a new empty sequence.
	extern const std::string DEFAULT_SEQUENCE_ID_PREFIX;
	
	/// Name used by default for a first stage of a new empty sequence.
	extern const std::string DEFAULT_FIRST_STAGE_NAME;

	/** Create an empty sequence with only one first stage, no moves, no objects and no resources. 
		All basic elements will be created with default infos. For example, the default space referential will be used.
		The Canvas area will be set to ( 1.0, 1.0, 1.0) vector space.

		@param sequence_name	Name of the sequence.
		@param sequence_id		Id of the sequence or empty if we should generate a unique id. 
		@param first_stage_id	Id to use of the first stage or empty if we should generate a default first stage id.
	**/
	aosl::Sequence make_empty_sequence(		const std::string& sequence_name
										,	const std::string& sequence_id = "" 
										,	const std::string& fist_stage_id = DEFAULT_FIRST_STAGE_NAME
									);
	
}


#endif
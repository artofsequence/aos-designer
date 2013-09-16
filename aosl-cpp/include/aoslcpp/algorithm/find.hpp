#ifndef HGUARD_AOSLCPP_FIND_HPP__
#define HGUARD_AOSLCPP_FIND_HPP__
#pragma once

#include "aosl/aosl_forward.hpp"

namespace aoslcpp
{

	/** (READ-ONLY) Search for the Object having the wanted id in a Canvas.
		We will search recursively in the objects trees.

		@param canvas		The canvas containing the object we're looking for.
		@param object_ref	Reference value corresponding to the id of the object we're looking for. 
		
		@return The Object we looked for or nullptr if not found.
	*/
	const aosl::Object* find_object( const aosl::Canvas& canvas, const aosl::Object_ref& object_ref );

	/** Search for the Object having the wanted id in a Canvas.
		We will search recursively in the objects trees.

		@param canvas		The canvas containing the object we're looking for.
		@param object_ref	Reference value corresponding to the id of the object we're looking for. 
		
		@return The Object we looked for or nullptr if not found.
	*/
	aosl::Object* find_object( aosl::Canvas& canvas, const aosl::Object_ref& object_ref );

	/** (READ-ONLY) Search for the Object having the wanted id in children of a given Object.
		We will search recursively in the tree.

		@param parent		Root of the tree of object we start looking in. Will be ignored in the search.
		@param object_ref	Reference value corresponding to the id of the object we're looking for. 
		
		@return The Object we looked for or nullptr if not found.
	*/
	const aosl::Object* find_object( const aosl::Object& parent, const aosl::Object_ref& object_ref );
	
	/** Search for the Object having the wanted id in children of a given Object.
		We will search recursively in the tree.

		@param parent		Root of the tree of object we start looking in. Will be ignored in the search.
		@param object_ref	Reference value corresponding to the id of the object we're looking for. 
		
		@return The Object we looked for or nullptr if not found.
	*/
	aosl::Object* find_object( aosl::Object& parent, const aosl::Object_ref& object_ref );
	

	/** (READ-ONLY) Search for the Move having the wanted id in a Story.
		@param story		Story containing the move we're looking for.
		@return The Object we looked for or nullptr if not found.
	*/
	const aosl::Move* find_move( const aosl::Story& story, const aosl::Move_ref& move_ref );
	
	/** Search for the Move having the wanted id in a Story.
		@param story		Story containing the move we're looking for.
		@return The Object we looked for or nullptr if not found.
	*/
	aosl::Move* find_move( aosl::Story& story, const aosl::Move_ref& move_ref );
	
	/** (READ-ONLY) Search for the Stage having the wanted id in a Story.
		@param story		Story containing the stage we're looking for.
		@return The Stage we looked for or nullptr if not found.
	*/
	const aosl::Stage* find_stage( const aosl::Story& story, const aosl::Stage_ref& stage_ref );
	
	/** Search for the Stage having the wanted id in a Story.
		@param story		Story containing the stage we're looking for.
		@return The Stage we looked for or nullptr if not found.
	*/
	aosl::Stage* find_stage( aosl::Story& story, const aosl::Stage_ref& stage_ref );
	
}


#endif

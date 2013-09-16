#ifndef HGUARD_AOSLCPP_FOREACH_HPP__
#define HGUARD_AOSLCPP_FOREACH_HPP__
#pragma once

#include <functional>
#include <utility>
#include "aosl/aosl_forward.hpp"
#include "aoslcpp/algorithm/iterator.hpp"

namespace aoslcpp
{
	
	/** Apply the given (READ-ONLY) function to every Object in the given root object (Canvas or Object), depth-first.
		The function will be called for all the objects of the object trees with depth-first algorithm.

		@param root			Object that contains the Objects we will iterate through. 
		@param func			Function to call for each Object.
	*/
	template< class FuncType, class RootType >
	void for_each_object_depth( const RootType& root, FuncType func )
	{
		std::for_each( objects_iterator_depth( root ), objects_iterator_depth(), [=]( const ObjectTreeNodeInfos& node )
		{
			func( *node.object() );
		});
	}

	/** Apply the given (READ-ONLY) function to every Object in the given root object (Canvas or Object), breadth-first.
		The function will be called for all the objects of the object trees with breadth-first algorithm.

		@param root			Object that contains the Objects we will iterate through. 
		@param func			Function to call for each Object.
	*/
	template< class FuncType, class RootType >
	void for_each_object_breadth( const RootType& root, FuncType func )
	{
		std::for_each( objects_iterator_breadth( root ), objects_iterator_breadth(), [=]( const ObjectTreeNodeInfos& node )
		{
			func( *node.object() );
		});
	}

	
}


#endif

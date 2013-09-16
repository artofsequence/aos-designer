#include "aoslcpp/algorithm/iterator.hpp"

#include <limits>

#include "aosl/object.hpp"
#include "aosl/canvas.hpp"

#include "utilcpp/assert.hpp"

namespace aoslcpp
{

	objects_iterator::objects_iterator()
		: m_node_idx( 0 )
	{
		
	}

	objects_iterator::objects_iterator( const objects_iterator& other )
		: m_node_idx( other.m_node_idx )
		, m_node_path( other.m_node_path )
	{

	}

	objects_iterator::objects_iterator( objects_iterator&& other )
		: m_node_idx( other.m_node_idx )
		, m_node_path( std::move( other.m_node_path ) )
	{

	}

	void objects_iterator::operator++()
	{
		if( !m_node_path.empty() && m_node_idx < m_node_path.size() )
		{
			++m_node_idx;
		}
			
	}


	ObjectTreeNodeInfos objects_iterator::operator*() const
	{
		if( !m_node_path.empty() && m_node_idx < m_node_path.size() )
		{
			return m_node_path[ m_node_idx ];
		}
		
		return ObjectTreeNodeInfos();
	}

	void objects_iterator::add_node( const ObjectTreeNodeInfos& node )
	{
		m_node_path.push_back( node );
	}


	void objects_iterator_depth::build( const aosl::Object_list& root_objects )
	{
		add_nodes( root_objects, nullptr, 0 );
		
	}

	void objects_iterator_depth::add_nodes( const aosl::Object_list& objects, const aosl::Object* parent, size_t depth )
	{
		const auto& object_list = objects.object();
		
		size_t idx = 0;
		for( const auto& object : object_list )
		{
			add_node( ObjectTreeNodeInfos( &object, parent, depth, idx ) );

			if( object.children() )
				add_nodes( *object.children(), &object, depth + 1 );

			++idx;
		};
	}

	objects_iterator_depth::objects_iterator_depth( const aosl::Object& object )
	{
		if( object.children() )
			build( *object.children() );
	}

	objects_iterator_depth::objects_iterator_depth( const aosl::Canvas& canvas )
	{
		build( canvas.objects() );
	}


	void objects_iterator_breadth::build( const aosl::Object_list& root_objects )
	{
		std::vector< Object_Parent > root_object_infos;
		const auto& root_object_list = root_objects.object();

		for( const auto& root_object : root_object_list )
		{
			Object_Parent infos;
			infos.object = &root_object;
			infos.parent = nullptr;
			root_object_infos.push_back( infos );
		};

		add_nodes( root_object_infos, 0 );

	}

	void objects_iterator_breadth::add_nodes( const std::vector< Object_Parent >& objects, size_t depth )
	{
		if( objects.empty() )
			return; // be lazy!

		std::vector<Object_Parent> child_objects;

		
		for( size_t idx = 0; idx < objects.size(); ++idx )
		{
			const Object_Parent& infos = objects[idx];
			add_node( ObjectTreeNodeInfos( infos.object, infos.parent, depth, idx ) );
			
			if( infos.object->children() ) // collect all the children at the same next depth level
			{
				const auto& children = infos.object->children()->object();
				for( const auto& child_object : children )
				{
					Object_Parent child_infos;
					child_infos.object = &child_object;
					child_infos.parent = infos.object;
					child_objects.push_back( child_infos );

				};
			}

		}

		if( !child_objects.empty() ) // go to the next depth level
			add_nodes( child_objects, depth + 1 );
	}

	objects_iterator_breadth::objects_iterator_breadth( const aosl::Object& object )
	{
		if( object.children() )
			build( *object.children() );
	}

	objects_iterator_breadth::objects_iterator_breadth( const aosl::Canvas& canvas )
	{
		build( canvas.objects() );
	}

}
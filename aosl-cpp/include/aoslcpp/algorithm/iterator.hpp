#ifndef HGUARD_AOSLCPP_ITERATOR_HPP__
#define HGUARD_AOSLCPP_ITERATOR_HPP__
#pragma once

#include <vector>
#include <iterator>

namespace aosl
{
	class Object;
	class Canvas;
	class Object_list;
}

namespace aoslcpp
{
	/** Tree node with informations about the node and the parent. */
	template< class T >
	class TreeNodeInfos
	{
	public:
		TreeNodeInfos() : m_object(nullptr), m_parent(nullptr), m_depth(0), m_idx(0) {}
		TreeNodeInfos( const T* object, const T* parent, size_t depth, size_t idx ) : m_object(object), m_parent(parent), m_depth(depth), m_idx(idx) {}
		
		const T* object() const { return m_object; }
		const T* parent() const { return m_parent; }

		size_t depth() const { return m_depth; }
		size_t idx() const { return m_idx; }

	private:
		const T* m_object;
		const T* m_parent;
		size_t m_depth;
		size_t m_idx;
	};

	template< class T >
	bool operator==( const TreeNodeInfos<T>& node_a, const TreeNodeInfos<T>& node_b )
	{
		if( !is_valid(node_a) && !is_valid(node_b) )
			return true;
		
		return node_a.object() == node_b.object()
			&& node_a.parent() == node_b.parent()
			&& node_a.depth() == node_b.depth()
			&& node_a.idx() == node_b.idx();
	}

	template< class T >
	bool is_valid( const TreeNodeInfos<T>& node ) { return node.object() != nullptr; }
	
	template< class T >
	bool is_root( const TreeNodeInfos<T>& node ) { return node.parent() == nullptr; }

	typedef TreeNodeInfos<aosl::Object> ObjectTreeNodeInfos;

	class objects_iterator 
		: public std::iterator< std::input_iterator_tag, ObjectTreeNodeInfos >
	{
	public:
		
		void operator++();
		ObjectTreeNodeInfos operator*() const;

	protected:

		typedef std::vector< ObjectTreeNodeInfos > NodePath;

		objects_iterator();
		objects_iterator( const objects_iterator& other );
		objects_iterator( objects_iterator&& other );
		
		virtual ~objects_iterator(){}

		void add_node( const ObjectTreeNodeInfos& node );

	private:

		size_t m_node_idx;
		NodePath m_node_path;

	};

	inline bool operator==( const objects_iterator& a, const objects_iterator& b )
	{
		return *a == *b;
	}

	inline bool operator!=( const objects_iterator& a, const objects_iterator& b )
	{
		return !(a == b);
	}


	class objects_iterator_breadth
		: public objects_iterator
	{
	public:

		objects_iterator_breadth(){}

		objects_iterator_breadth( const objects_iterator_breadth& other ) : objects_iterator( other ) {}
		objects_iterator_breadth( objects_iterator_breadth&& other ) : objects_iterator( other ) {}

		explicit objects_iterator_breadth( const aosl::Object& object );
		explicit objects_iterator_breadth( const aosl::Canvas& canvas );


		static inline objects_iterator_breadth end() { return objects_iterator_breadth(); }
		template< class T >
		static inline objects_iterator_breadth begin( const T& root ) { return objects_iterator_breadth(root); }

	private:

		

		void build( const aosl::Object_list& root_objects );

		struct Object_Parent {  const aosl::Object* object; const aosl::Object* parent; };

		void add_nodes( const std::vector< Object_Parent >& objects, size_t depth );

	};

	class objects_iterator_depth
		: public objects_iterator
	{
	public:

		objects_iterator_depth(){}
		objects_iterator_depth( const objects_iterator_depth& other ) : objects_iterator( other ) {}
		objects_iterator_depth( objects_iterator_depth&& other ) : objects_iterator( other ) {}

		explicit objects_iterator_depth( const aosl::Object& object );
		explicit objects_iterator_depth( const aosl::Canvas& canvas );

		static inline objects_iterator_depth end() { return objects_iterator_depth(); }
		template< class T >
		static inline objects_iterator_depth begin( const T& root ) { return objects_iterator_depth(root); }

		
	private:

		
		void build( const aosl::Object_list& root_objects );

		void add_nodes( const aosl::Object_list& objects, const aosl::Object* parent, size_t depth );

	};

}


#endif

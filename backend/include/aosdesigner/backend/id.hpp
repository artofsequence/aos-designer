#ifndef HGUARD_AOSD_BACKEND_ID_HPP__
#define HGUARD_AOSD_BACKEND_ID_HPP__

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <utilcpp/assert.hpp>

namespace aosd {
namespace backend {

	template< class T >
	class Id
	{
	public:
		
		typedef Id<T>				ThisType;
		typedef boost::uuids::uuid	ValueType;

		static const ThisType INVALID;			///< Invalid id.

		/// Default constructor, set this id to invalid value.
		Id() : m_value( INVALID.value() ) {}

		/// Constructor converting from an internal value.
		Id( ValueType value ) : m_value( std::move(value) ) {}
		
		/// Destruction of an id mark it as invalid to make sure it's
		~Id(){ *this = INVALID; }

		const ValueType& value() const { return m_value; }
		operator ValueType () const { return m_value; }

	private:

		ValueType m_value;

	};

	template< class T >
	const Id<T> Id<T>::INVALID = boost::uuids::nil_uuid();

	template< class T >
	bool operator==( const Id<T>&left, const Id<T>& right ) { return left.value() == right.value(); }

	template< class T >
	bool operator!=( const Id<T>&left, const Id<T>& right ) { return !(left == right); }

	template< class T >
	bool operator<( const Id<T>&left, const Id<T>& right ) { return left.value() < right.value(); }

	template< class T >
	bool operator>( const Id<T>&left, const Id<T>& right ) { return left.value() > right.value(); }

	template< class T >
	bool operator<=( const Id<T>&left, const Id<T>& right ) { return left.value() <= right.value(); }

	template< class T >
	bool operator>=( const Id<T>&left, const Id<T>& right ) { return left.value() >= right.value(); }
	
	template< class T >
	bool is_valid( const Id<T>& id ) { return id != Id<T>::INVALID; }
	
	template< class T >
	std::string to_string( const Id<T>& id ) 
	{ 
		using namespace std; 
		return to_string(id.value()); 
	}

	template< class T >
	std::string to_bytes( const Id<T>& id ) 
	{ 
		using namespace std; 
		return std::string( begin(id.value()), end(id.value()) );  
	}

	template< class T >
	size_t hash_value( const Id<T>& id ) 
	{ 
		using namespace boost::uuids;
		return hash_value(id.value()); 
	}

	template< class T >
	size_t tbb_hasher( const Id<T>& id ) { using namespace boost::uuids; return hash_value(id); }
	
	/** Generate a new id.
		This is thread-safe. 
		The new id will be generated randomly as a UUID.
	*/
	template< class T >
	Id<T> make_id()
	{
		Id<T>::ValueType generate_random_id();

		const auto new_id = Id<T>( generate_random_id() );
		UTILCPP_ASSERT( is_valid(new_id), "Generated an invalid id for type " << typeid(T).name() );
		return new_id;
	}

	
}}

namespace std
{
	template < class U > struct hash;

	template < class T > 
	struct hash< aosd::backend::Id<T> >
	{
		size_t operator()(const aosd::backend::Id<T> & id ) const
		{
			using namespace boost::uuids;
			return hash_value( id );
		}
	};
}

#endif

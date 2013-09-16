#include <aosdesigner/backend/id.hpp>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/thread/synchronized_value.hpp>

namespace aosd {
namespace backend {


namespace detail {
	
	IdValueType generate_random_id()
	{
		using namespace boost;
		static synchronized_value<uuids::random_generator> generator;
		
		return generator->operator()();
	}

}
}}

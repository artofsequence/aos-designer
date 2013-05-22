#include <aosdesigner/backend/id.hpp>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace aosd {
namespace backend {

	namespace {
		boost::mutex id_gen_mutex;
	}

namespace detail {
	
	IdValueType generate_random_id()
	{
		static boost::uuids::random_generator generator;
		boost::lock_guard<boost::mutex> _(id_gen_mutex);

		return generator();
	}

}
}}

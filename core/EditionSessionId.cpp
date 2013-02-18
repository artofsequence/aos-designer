#include "EditionSessionId.hpp"

#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

namespace aosd
{
namespace core
{

	static const EditionSessionId EditionSessionId_INVALID = to_string( boost::uuids::nil_generator()() );

	bool is_valid( const EditionSessionId& session_id )
	{
		return !session_id.empty() 
			&& session_id != EditionSessionId_INVALID
			;
	}
	
}
}
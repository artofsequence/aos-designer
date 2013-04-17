#include <memory>

#include "application.hpp"
#include "utilcpp/log.hpp"




int main( int arg_count, char** arg_array )
{
	// TODO : add basic memory leak detector (VLD)

	// TODO : add exception handling here
	auto app = std::unique_ptr<aosd::Application>( new aosd::Application( arg_count, arg_array ) );
	auto result = app->run();

	return result;
}
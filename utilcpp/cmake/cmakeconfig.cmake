
option( UTILCPP_DEBUG_CMAKE_MACRO
	"Turn this ON display more messages from CMake scripts of project files." 
	OFF
)

option( UTILCPP_VLD_ENABLED
	"Enable Visual Leak Detector if MSVC and assume it is installed."
	OFF
)

option( UTILCPP_FORCE_GENERATE_LIBRARIES_API 
	"Turn this ON to force (re)generation of api.hpp files in all library projects." 
	OFF
)
	

set( UTILCPP_PROJECT_API_HEADER_TEMPLATE	${UTILCPP_CMAKE_DIR}/library_api.hpp.template
	CACHE STRING 
	"Path of the file to use as template to generate the API header used in shared libraries." )
	
set( UTILCPP_STATIC_API_HEADER_TEMPLATE	${UTILCPP_CMAKE_DIR}/static_library_api.hpp.template
	CACHE STRING 
	"Path of the file to use as template to generate the API header used in static libraries." )

set( UTILCPP_PROJECT_API_HEADER_NAME	"api.hpp"
	CACHE STRING 
	"Name of the API header file generated for all the library projects." )




# Allow virtual directories for grouping projects in IDEs.
set_property( GLOBAL PROPERTY USE_FOLDERS ON )



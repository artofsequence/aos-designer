#ifndef HGUARD_AOSD_BACKEND_API_HPP__
#define HGUARD_AOSD_BACKEND_API_HPP__

#include <utilcpp/moduleapi.hpp>
#ifdef AOSD_BACKEND_EXPORT
#	define AOSD_BACKEND_API	UCX_MODULE_API_EXPORT
#else
#	define AOSD_BACKEND_API	UCX_MODULE_API_IMPORT
#endif


#endif

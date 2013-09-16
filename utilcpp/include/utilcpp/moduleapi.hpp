#ifndef HGUARD_UTILCXX_MODULEAPI_HPP__
#define HGUARD_UTILCXX_MODULEAPI_HPP__

#include "platforminfo.hpp"


#if UCX_COMPILER == UCX_COMPILER_MSVC

	/// MSVC implementation of module API macro
#	define UCX_MODULE_API_IMPORT   __declspec( dllimport )
#	define UCX_MODULE_API_EXPORT   __declspec( dllexport )

#else

	/// GCC(-like) implementation of module API macro
#	define UCX_MODULE_API_IMPORT   __attribute__ ((visibility("default")))
#	define UCX_MODULE_API_EXPORT   __attribute__ ((visibility("default")))

#endif 

#endif


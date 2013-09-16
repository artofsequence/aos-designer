#ifndef HGUARD_UTILCXX_PLATFORMINFO_HPP__
#define HGUARD_UTILCXX_PLATFORMINFO_HPP__


#define UCX_PLATFORM_WINDOWS	1		///< Win32 Architecture (Windows98, WindowsXP, Vista)
#define UCX_PLATFORM_MACOSX		2		///< Apple OS (OSX)
#define	UCX_PLATFORM_LINUX		3		///< Linux based OS (various, Ubuntu and Fedora as first target?)

// Find which platform it is.
#if defined( WIN32 ) || defined( _WIN32 )	

	/// We are on Win32 operating system (windows98, windowsXP, Vista).
	#define UCX_PLATFORM		UCX_PLATFORM_WINDOWS

#elif defined( __APPLE_CC__)

	/// We are on an APPLE operating system (MacOSX)
	#define UCX_PLATFORM		UCX_PLATFORM_MACOSX

#else 

	/// We are on a LINUX based operating system.
	#define UCX_PLATFORM		UCX_PLATFORM_LINUX

#endif

// Target os architectures
#define UCX_OS_ARCHITECTURE_32	32	///< 32bit Architecture Operating System
#define UCX_OS_ARCHITECTURE_64	64	///< 64bit Architecture Operating System

// Find which architecture it is
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)

	/// We are on a 64bit Architecture Operating System 
	#define UCX_OS_ARCHITECTURE	UCX_OS_ARCHITECTURE_64	

#else

	/// We are on a 32bit Architecture Operating System
	#define UCX_OS_ARCHITECTURE	UCX_OS_ARCHITECTURE_32

#endif


#define UCX_COMPILER_MSVC 1
#define UCX_COMPILER_GNUC 2
#define UCX_COMPILER_BORL 3
#define UCX_COMPILER_WINSCW 4
#define UCX_COMPILER_GCCE 5
#define UCX_COMPILER_CLANG 6

/* Finds the compiler type and version.
*/
#if defined( __GCCE__ )
#   define UCX_COMPILER UCX_COMPILER_GCCE
#   define UCX_COMP_VER _MSC_VER
//#	include <staticlibinit_gcce.h> // This is a GCCE toolchain workaround needed when compiling with GCCE 
#elif defined( __WINSCW__ )
#   define UCX_COMPILER UCX_COMPILER_WINSCW
#   define UCX_COMP_VER _MSC_VER
#elif defined( _MSC_VER )
#   define UCX_COMPILER UCX_COMPILER_MSVC
#   define UCX_COMP_VER _MSC_VER
#elif defined( __clang__ )
#   define UCX_COMPILER UCX_COMPILER_CLANG
#   define UCX_COMP_VER (((__clang_major__)*100) + \
	(__clang_minor__*10) + \
	__clang_patchlevel__)
#elif defined( __GNUC__ )
#   define UCX_COMPILER UCX_COMPILER_GNUC
#   define UCX_COMP_VER (((__GNUC__)*100) + \
	(__GNUC_MINOR__*10) + \
	__GNUC_PATCHLEVEL__)
#elif defined( __BORLANDC__ )
#   define UCX_COMPILER UCX_COMPILER_BORL
#   define UCX_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif


#if defined(DEBUG) || defined(_DEBUG)
#	define UCX_DEBUG /// Debug Mode activated.
#endif


#endif

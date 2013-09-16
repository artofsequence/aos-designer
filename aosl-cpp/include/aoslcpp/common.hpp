#ifndef HGUARD_AOSLCPP_COMMON_HPP__
#define HGUARD_AOSLCPP_COMMON_HPP__

#ifndef XSD_NO_EXPORT
#define XSD_NO_EXPORT
#endif

#if defined(WIN32) //windows specific

///Specific Win32 DLL Import macro :
#define AOSLCPP_DllImport   __declspec( dllimport )
///Specific Win32 DLL Export macro :
#define AOSLCPP_DllExport   __declspec( dllexport )

#else

//Non-Windows specifics.
#error Define non-windows shared macro export/import
/// Import macro :
#define AOSLCPP_DllImport 
/// Export macro :
#define AOSLCPP_DllExport 

#endif


#ifdef AOSLCPP_SOURCE
///Import / Export of dynamic lib functions/classes
#define AOSLCPP_API AOSLCPP_DllExport
#else
///Import / Export of dynamic lib functions/classes
#define AOSLCPP_API AOSLCPP_DllImport
#endif

namespace aosl
{
	extern const char* AOSL_XML_NAMESPACE_NAME;
}


#endif
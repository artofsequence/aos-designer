#ifndef HGUARD_UTILCPP_HARDCONFIG_HPP__
#define HGUARD_UTILCPP_HARDCONFIG_HPP__
#pragma once


#ifndef UTILCPP_DEBUG_LOG_ON 
	#ifdef _DEBUG 
		#define UTILCPP_DEBUG_LOG_ON 1
	#else
		#define UTILCPP_DEBUG_LOG_ON 0
	#endif
#endif

#ifndef UTILCPP_ASSERTIONS_ON 
	#ifdef _DEBUG 
		#define UTILCPP_ASSERTIONS_ON 1
	#else
		#define UTILCPP_ASSERTIONS_ON 0
	#endif
#endif

#ifndef UTILCPP_ASSERTIONS_LOG_ON 
	#ifdef _DEBUG 
		#define UTILCPP_ASSERTIONS_LOG_ON 1
	#else
		#define UTILCPP_ASSERTIONS_LOG_ON 0
	#endif
#endif

#ifndef UTILCPP_ASSERTIONS_DEBUGBREAK_ON 
	#ifdef _DEBUG 
		#define UTILCPP_ASSERTIONS_DEBUGBREAK_ON 1
	#else
		#define UTILCPP_ASSERTIONS_DEBUGBREAK_ON 0
	#endif
#endif

#ifndef UTILCPP_ASSERTIONS_CRASH_ON 
	#ifdef _DEBUG 
		#define UTILCPP_ASSERTIONS_CRASH_ON 1
	#else
		#define UTILCPP_ASSERTIONS_CRASH_ON 0
	#endif
#endif


#endif
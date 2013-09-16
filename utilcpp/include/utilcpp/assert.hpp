#ifndef HGUARD_UTILCPP_ASSERT_HPP__
#define HGUARD_UTILCPP_ASSERT_HPP__
#pragma once

#include <exception>

#include "utilcpp/hardconfig.hpp"
#include "utilcpp/log.hpp"


#define UTILCPP_DEBUGBREAK ::__debugbreak() // is it crossplatform?

#if UTILCPP_ASSERTIONS_LOG_ON == 1
	#define UTILCPP_ASSERTIONS_LOG( expression__, message__ ) \
		UTILCPP_LOG_ERROR	<< "\n#############################################" \
							<< "\n#### Assertion Failed! : " << #expression__ \
							<< "\n## Function : "	<< __FUNCTION__ \
							<< "\n## File : "		<< __FILE__ \
							<< "\n## Line : "		<< __LINE__ \
							<< "\n##" \
							<< "\n## Message : \n\t\t"	<< message__  \
							<< "\n##" \
							<< "\n#############################################\n\n";
#else 
	#define UTILCPP_ASSERTIONS_LOG( expression__, message__ )
#endif

#if UTILCPP_ASSERTIONS_DEBUGBREAK_ON == 1
	#define UTILCPP_ASSERTIONS_DEBUGBREAK UTILCPP_DEBUGBREAK
#else 
	#define UTILCPP_ASSERTIONS_DEBUGBREAK
#endif

#if UTILCPP_ASSERTIONS_CRASH_ON == 1
	#define UTILCPP_ASSERTIONS_CRASH  std::terminate()
#else 
	#define UTILCPP_ASSERTIONS_CRASH
#endif

#define UTILCPP_ASSERTION_IMPLEMENTATION( expression__, message__ ) \
			UTILCPP_ASSERTIONS_LOG( expression__, message__ ); \
			UTILCPP_ASSERTIONS_DEBUGBREAK; \
			UTILCPP_ASSERTIONS_CRASH;


#if UTILCPP_ASSERTIONS_ON == 1

	#define UTILCPP_ASSERT( expression__, message__ ) if( !(expression__) ) { UTILCPP_ASSERTION_IMPLEMENTATION( expression__, message__ ); }

	#define UTILCPP_ASSERT_NULL( expression__ ) UTILCPP_ASSERT( !(expression__), #expression__ " IS NOT NULL! It should be!" )
	#define UTILCPP_ASSERT_NOT_NULL( expression__ ) UTILCPP_ASSERT( expression__, #expression__ " IS NULL! It shouldn't be!" )

	#define UTILCPP_ASSERT_IMPOSSIBLE( message__ ) UTILCPP_ASSERTION_IMPLEMENTATION( "IMPOSSIBLE!!!", message__ )

#else
	
	#define UTILCPP_ASSERT( expression__, message__ )
	#define UTILCPP_ASSERT_NULL( expression__ )
	#define UTILCPP_ASSERT_NOT_NULL( expression__ )

	#define UTILCPP_ASSERT_IMPOSSIBLE( message__ )

#endif

/////////////////////////////////////////////
// some utility macros

/// Use this macro in functions wich implementation will be written later.
#define UTILCPP_NOT_IMPLEMENTED_YET \
	UTILCPP_LOG_ERROR	<< "\n##########################################" \
					<< "\n## !!!! NOT IMPLEMENTED YET !!! " \
					<< "\n## Function : "	<< __FUNCTION__ \
					<< "\n## File : "		<< __FILE__ \
					<< "\n## Line : "		<< __LINE__ \
					<< "\n##########################################\n" \
					; \
					UTILCPP_DEBUGBREAK

/// Use this macro when you just want to remember to implement a function before compiling
#define UTILCPP_DO_IT_NOW	static_assert( false, "NOT IMPLEMENTED : DO IT NOW!" )


#endif

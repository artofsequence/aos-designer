#ifndef HGUARD_UTILCPP_LOG_HPP__
#define HGUARD_UTILCPP_LOG_HPP__
#pragma once

#include <string>
#include <sstream>
#include <functional>

#include "utilcpp/hardconfig.hpp"

/* Logging macros :

   UTILCPP_LOG << "Hello World? " << 42 ; // log a message 
   UTILCPP_LOG_ERROR << "SOMETHING IS WRONG!" << 666 ; // log an error
   UTILCPP_LOG_DEBUG << "About this value ..." << iterator << ", did you know?" ; // log debug informations
*/



#define UTILCPP_LOG_WITH_LEVEL( log_level )		util::Log( log_level )
#define UTILCPP_LOG								UTILCPP_LOG_WITH_LEVEL( util::Log::INFO )
#define UTILCPP_LOG_ERROR						UTILCPP_LOG_WITH_LEVEL( util::Log::ERROR )

#define UTILCPP_LOG_NOTHING						if(false) util::NoLog() 


#if UTILCPP_DEBUG_LOG_ON == 1
#define UTILCPP_LOG_DEBUG						UTILCPP_LOG_WITH_LEVEL( util::Log::DEBUG )
#else 
#define UTILCPP_LOG_DEBUG UTILCPP_LOG_NOTHING
#endif

namespace util
{

	
	/** NO DOCUMENTATION YET!
	*/
	class Log
	{
	public:

		enum Level
		{
			ERROR
		,	INFO
		,	DEBUG
		};

		static const char* name( Level level );

		Log( Level level );
		~Log();

		template< typename T >
		Log& operator<<( const T& message )
		{
			m_stream << message;
			return *this;
		}


	private:
		
		Level m_level;
		std::stringstream m_stream;

		void log();

	};

	class NoLog
	{
	public:
		template< typename T >
		void operator<<( const T& message )
		{ }
	};


	typedef std::function< void ( Log::Level level, const std::string& ) > LogOutput;

	void register_log_output( LogOutput output, int id );
	void unregister_log_output( int id );


}


#endif
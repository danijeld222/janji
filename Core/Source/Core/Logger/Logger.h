#pragma once

#include "Core/Defines.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

enum LogLevel
{
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_INFO = 3,
	LOG_LEVEL_DEBUG = 4,
	LOG_LEVEL_TRACE = 5,
};

namespace Core
{
	class COREAPI Logger
	{
	public:
		static void Initialize();
		static void LogOutput(LogLevel level, const char* message, ...);

	private:
		// Windows specific console output, won't work on any other OS
		static void ConsoleWrite(const char* message, u8 color);
		static void ConsoleWriteError(const char* message, u8 color);
	};
}

// Log defines
#define COREFATAL(message, ...) Core::Logger::LogOutput(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#define COREERROR(message, ...) Core::Logger::LogOutput(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);

#if LOG_WARNING_ENABLED == 1
#define COREWARNING(message, ...) Core::Logger::LogOutput(LOG_LEVEL_WARNING, message, ##__VA_ARGS__);
#else
#define COREWARNING(message,...)
#endif 

#if LOG_INFO_ENABLED == 1
#define COREINFO(message, ...) Core::Logger::LogOutput(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define COREINFO(message,...)
#endif 

#if LOG_DEBUG_ENABLED == 1
#define COREDEBUG(message, ...) Core::Logger::LogOutput(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define COREDEBUG(message,...)
#endif 

#if LOG_TRACE_ENABLED == 1
#define CORETRACE(message, ...) Core::Logger::LogOutput(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define CORETRACE(message,...)
#endif 
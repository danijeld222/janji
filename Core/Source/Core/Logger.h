#pragma once

#include "Defines.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum LogLevel
{
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR = 1,
	LOG_LEVEL_WARNING = 2,
	LOG_LEVEL_INFO = 3,
	LOG_LEVEL_DEBUG = 4,
	LOG_LEVEL_TRACE = 5,
} LogLevel;

b8 InitializeLogging();
void ShutdownLogging();

COREAPI void LogOutput(LogLevel Level, const char* Message, ...);

// Log defines
#define COREFATAL(Message, ...) LogOutput(LOG_LEVEL_FATAL, Message, ##__VA_ARGS__);
#define COREERROR(Message, ...) LogOutput(LOG_LEVEL_ERROR, Message, ##__VA_ARGS__);

#if LOG_WARNING_ENABLED == 1
#define COREWARNING(Message, ...) LogOutput(LOG_LEVEL_WARNING, Message, ##__VA_ARGS__);
#else
#define COREWARNING(Message,...)
#endif 

#if LOG_INFO_ENABLED == 1
#define COREINFO(Message, ...) LogOutput(LOG_LEVEL_INFO, Message, ##__VA_ARGS__);
#else
#define COREINFO(Message,...)
#endif 

#if LOG_DEBUG_ENABLED == 1
#define COREDEBUG(Message, ...) LogOutput(LOG_LEVEL_DEBUG, Message, ##__VA_ARGS__);
#else
#define COREDEBUG(Message,...)
#endif 

#if LOG_TRACE_ENABLED == 1
#define CORETRACE(Message, ...) LogOutput(LOG_LEVEL_TRACE, Message, ##__VA_ARGS__);
#else
#define CORETRACE(Message,...)
#endif 
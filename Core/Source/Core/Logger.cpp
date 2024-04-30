#include "Logger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 InitializeLogging()
{
	return true;
}

void ShutdownLogging()
{
	 
}

void LogOutput(LogLevel Level, const char* Message, ...)
{
	const char* LevelStrings[6] = { "[FATAL]:  ", "[ERROR]:  ", "[WARNING]:", "[INFO]:   ", "[DEBUG]:  ", "[TRACE]:  " };
	b8 IsError = (Level < 2);
	
	char OutMessage[32000];
	memset(OutMessage, 0, sizeof(OutMessage));

	va_list arg_ptr;
	va_start(arg_ptr, Message);
	vsnprintf(OutMessage, 32000, Message, arg_ptr);
	va_end(arg_ptr);

	char OutMessage2[32000];
	sprintf_s(OutMessage2, "%s%s\n", LevelStrings[Level], OutMessage);
	printf("%s", OutMessage2);
}
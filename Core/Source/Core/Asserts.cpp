#include "Asserts.h"
#include "Logger.h"

void ReportAssertionFailure(const char* Expression, const char* Message, const char* File, i32 Line)
{
	LogOutput(LOG_LEVEL_FATAL, "Assertion Failure: %s, Message: '%s', in File: %s, Line: %d\n", Expression, Message, File, Line);
}
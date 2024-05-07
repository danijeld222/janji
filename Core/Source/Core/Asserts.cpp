#include "Asserts.h"
#include "Logger/Logger.h"

void ReportAssertionFailure(const char* expression, const char* message, const char* file, i32 line)
{
	Core::Logger::LogOutput(LOG_LEVEL_FATAL, "Assertion Failure: %s, Message: '%s', in File: %s, Line: %d\n", expression, message, file, line);
}
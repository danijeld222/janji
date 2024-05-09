#include "Logger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <windows.h>
#include <stdlib.h>

namespace Core
{
	void Logger::Initialize()
	{
		// Initialize
	}
	
	void Logger::Shutdown()
	{
		// Shutdown
	}
	
	void Logger::LogOutput(LogLevel level, const char* message, ...)
	{
		const char* levelStrings[6] = { "[FATAL]:  ", "[ERROR]:  ", "[WARNING]:", "[INFO]:   ", "[DEBUG]:  ", "[TRACE]:  " };
		b8 isError = (level < LOG_LEVEL_WARNING);

		const i32 messageLength = 32000;
		char outMessage[messageLength];
		memset(outMessage, 0, sizeof(outMessage));

		va_list arg_ptr;
		va_start(arg_ptr, message);
		vsnprintf(outMessage, messageLength, message, arg_ptr);
		va_end(arg_ptr);

		char outMessageReformated[messageLength];
		sprintf_s(outMessageReformated, "%s%s\n", levelStrings[level], outMessage);

		if (isError)
		{
			ConsoleWriteError(outMessageReformated, level);
		}
		else
		{
			ConsoleWrite(outMessageReformated, level);
		}
	}

	// These are windows specific calls, won't work on any other OS
	void Logger::ConsoleWrite(const char* message, u8 color)
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		static u8 levels[6] = { 64, 4, 6, 2, 1, 8 }; // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		SetConsoleTextAttribute(consoleHandle, levels[color]);
		OutputDebugStringA(message);
		u64 length = strlen(message);
		LPDWORD numberWritten = 0;
		WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, numberWritten, 0);

		// Reset console text color to white
		SetConsoleTextAttribute(consoleHandle, 7);
	}

	void Logger::ConsoleWriteError(const char* message, u8 color)
	{
		HANDLE consoleHandle = GetStdHandle(STD_ERROR_HANDLE);
		static u8 levels[6] = { 64, 4, 6, 2, 1, 8 }; // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
		SetConsoleTextAttribute(consoleHandle, levels[color]);
		OutputDebugStringA(message);
		u64 length = strlen(message);
		LPDWORD numberWritten = 0;
		WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, numberWritten, 0);

		// Reset console text color to white
		SetConsoleTextAttribute(consoleHandle, 7);
	}
}
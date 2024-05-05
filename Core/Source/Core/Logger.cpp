#include "Logger.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <windows.h>
#include <stdlib.h>

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
	b8 IsError = (Level < LOG_LEVEL_WARNING);
	
	const i32 MessageLength = 32000;
	char OutMessage[MessageLength];
	memset(OutMessage, 0, sizeof(OutMessage));

	va_list arg_ptr;
	va_start(arg_ptr, Message);
	vsnprintf(OutMessage, MessageLength, Message, arg_ptr);
	va_end(arg_ptr);

	char OutMessage2[MessageLength];
	sprintf_s(OutMessage2, "%s%s\n", LevelStrings[Level], OutMessage);
	
	if (IsError)
	{
		ConsoleWriteError(OutMessage2, Level);
	}
	else
	{
		ConsoleWrite(OutMessage2, Level);
	}
}

// These are windows specific calls, won't work on any other OS
void ConsoleWrite(const char* Message, u8 Color)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	static u8 Levels[6] = { 64, 4, 6, 2, 1, 8 }; // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	SetConsoleTextAttribute(ConsoleHandle, Levels[Color]);
	OutputDebugStringA(Message);
	u64 Length = strlen(Message);
	LPDWORD NumberWritten = 0;
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), Message, (DWORD)Length, NumberWritten, 0);

	// Reset console text color to white
	SetConsoleTextAttribute(ConsoleHandle, 7);
}

void ConsoleWriteError(const char* Message, u8 Color)
{
	HANDLE ConsoleHandle = GetStdHandle(STD_ERROR_HANDLE);
	static u8 Levels[6] = { 64, 4, 6, 2, 1, 8 }; // FATAL,ERROR,WARN,INFO,DEBUG,TRACE
	SetConsoleTextAttribute(ConsoleHandle, Levels[Color]);
	OutputDebugStringA(Message);
	u64 Length = strlen(Message);
	LPDWORD NumberWritten = 0;
	WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), Message, (DWORD)Length, NumberWritten, 0);

	// Reset console text color to white
	SetConsoleTextAttribute(ConsoleHandle, 7);
}

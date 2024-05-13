#pragma once

#include "Defines.h"

#pragma warning(disable : 5105)

#define COREASSERTIONS_ENABLED 1

#if defined COREASSERTIONS_ENABLED
#if defined _MSC_VER
#include <intrin.h>
#define COREDebugBreak() __debugbreak()
#else
#define COREDebugBreak()
#endif

void ReportAssertionFailure(const char* expression, const char* message, const char* file, i32 line);

#define COREASSERT(expression)													\
{																				\
	if (expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#expression, "", __FILE__, __LINE__);			\
		COREDebugBreak();														\
	}																			\
}

#define COREASSERT_MESSAGE(expression, message)									\
{																				\
	if (expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#expression, message, __FILE__, __LINE__);		\
		COREDebugBreak();														\
	}																			\
}

#ifdef DEBUG
#define COREASSERT_DEBUG(expression)											\
{																				\
	if (expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#expression, "", __FILE__, __LINE__);			\
		COREDebugBreak();														\
	}																			\
}
#else
#define COREASSERT_DEBUG(expression)
#endif

#else
#define COREASSERT(expression)
#define COREASSERT_MESSAGE(expression)
#define COREASSERT_DEBUG(expression)
#endif
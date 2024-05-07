#pragma once

#include "Defines.h"

#define COREASSERTIONS_ENABLED 1

#if defined COREASSERTIONS_ENABLED
#if defined _MSC_VER
#include <intrin.h>
#define DebugBreak() __debugbreak()
#else
#define DebugBreak()
#endif

COREAPI void ReportAssertionFailure(const char* expression, const char* message, const char* file, i32 line);

#define COREASSERT(expression)													\
{																				\
	if (expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#expression, "", __FILE__, __LINE__);			\
		DebugBreak();															\
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
		DebugBreak();															\
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
		DebugBreak();															\
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
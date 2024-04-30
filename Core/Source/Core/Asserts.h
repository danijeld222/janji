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

COREAPI void ReportAssertionFailure(const char* Expression, const char* Message, const char* File, i32 Line);

#define COREASSERT(Expression)													\
{																				\
	if (Expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#Expression, "", __FILE__, __LINE__);			\
		DebugBreak();															\
	}																			\
}

#define COREASSERT_MESSAGE(Expression, Message)									\
{																				\
	if (Expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#Expression, Message, __FILE__, __LINE__);		\
		DebugBreak();															\
	}																			\
}

#ifdef DEBUG
#define COREASSERT_DEBUG(Expression)											\
{																				\
	if (Expression)																\
	{																			\
	}																			\
	else																		\
	{																			\
		ReportAssertionFailure(#Expression, "", __FILE__, __LINE__);			\
		DebugBreak();															\
	}																			\
}
#else
#define COREASSERT_DEBUG(Expression)
#endif

#else
#define COREASSERT(Expression)
#define COREASSERT_MESSAGE(Expression)
#define COREASSERT_DEBUG(Expression)
#endif
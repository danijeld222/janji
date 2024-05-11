#pragma once

#include "Core/Defines.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if RELEASE == 1
#define LOG_TRACE_ENABLED 0
#endif

namespace Core
{
	class Logger
	{
	public:
		static void Initialize();
		static void Shutdown();
		
		inline static std::shared_ptr <spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

// Log defines
#define CORECRITICAL(...) Core::Logger::GetCoreLogger()->critical(__VA_ARGS__);
#define COREERROR(...) Core::Logger::GetCoreLogger()->error(__VA_ARGS__);

#if LOG_WARNING_ENABLED == 1
#define COREWARNING(...) Core::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#else
#define COREWARNING(...)
#endif 

#if LOG_INFO_ENABLED == 1
#define COREINFO(...) Core::Logger::GetCoreLogger()->info(__VA_ARGS__);
#else
#define COREINFO(...)
#endif 

#if LOG_TRACE_ENABLED == 1
#define CORETRACE(...) Core::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#else
#define CORETRACE(...)
#endif 
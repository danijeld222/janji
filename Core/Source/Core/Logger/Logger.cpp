#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Core
{
	Ref<spdlog::logger> Logger::s_CoreLogger;

	void Logger::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("CORE");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
	
	void Logger::Shutdown()
	{
		// Shutdown
	}
}
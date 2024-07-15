#pragma once

#include "Core/Debug/Instrumentor.h"

extern Core::Application* Core::CreateApplication();

int main(int argc, char** argv)
{
	CORE_PROFILE_BEGIN_SESSION("Startup", "CoreProfile-Startup.json");
	auto app = Core::CreateApplication();
	CORE_PROFILE_END_SESSION();
	
	CORE_PROFILE_BEGIN_SESSION("Runtime", "CoreProfile-Runtime.json");
	app->ApplicationRun();
	CORE_PROFILE_END_SESSION();
	
	CORE_PROFILE_BEGIN_SESSION("Startup", "CoreProfile-Shutdown.json");
	delete app;
	CORE_PROFILE_END_SESSION();
}
#pragma once

extern Core::Application* Core::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Core::CreateApplication();
	app->ApplicationRun();
	delete app;
}
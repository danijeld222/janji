#pragma once

#include "Core/Defines.h"
#include "Core/Events/Event.h"
#include <string>

namespace Core
{
	struct WindowSettings
	{
		const char* title;
		u32 width;
		u32 height;
		u32 windowFlags;
		
		WindowSettings(const char* windowTitle = (char*)"Janji", u32 windowWidth = 1280, u32 windowHeight = 720, u32 _windowFlags = 0)
			: title(windowTitle), width(windowWidth), height(windowHeight), windowFlags(_windowFlags)
		{
		}
	};

	class WindowBase
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;
		
		virtual ~WindowBase() {}
		virtual void OnUpdate() = 0; // https://stackoverflow.com/questions/2652198/difference-between-a-virtual-function-and-a-pure-virtual-function
		
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		
		virtual void InitRenderer() = 0;
		virtual void* GetRenderer() const = 0;
		virtual void RendererBegin() const = 0;
		virtual void RendererUpdate() const = 0;
		virtual void RendererSwapBuffers() const = 0;
		
		virtual void* GetNativeWindow() const = 0;
		
		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		static WindowBase* Create(const WindowSettings& settings = WindowSettings());
	};
}
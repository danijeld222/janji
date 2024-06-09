#pragma once

#include "WindowBase.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RendererContext.h"

#include <SDL3/SDL.h>

namespace Core 
{
	class Window : public WindowBase
	{
	public:
		Window(const WindowSettings& props);
		virtual ~Window();
		
		void OnUpdate() override;
		
		inline u32 GetWidth() const override { return m_Data.width; }
		inline u32 GetHeight() const override { return m_Data.height; }
		
		virtual void* GetRendererContext()	const override { return m_RendererContext; };
		
		inline virtual void* GetNativeWindow() const override { return m_Window; }
		
		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.eventCallback = callback; }
		
		static i32 HandleWindowResizeEvent(void* data, SDL_Event* e);
		static i32 HandleWindowCloseEvent(void* data, SDL_Event* e);
		static i32 HandleKeyboardEvent(void* data, SDL_Event* e);
		static i32 HandleMouseButtonEvent(void* data, SDL_Event* e);
		static i32 HandleMouseScrollEvent(void* data, SDL_Event* e);
		static i32 HandleMouseMoveEvent(void* data, SDL_Event* e);
		
	private:
		virtual void Initialize(const WindowSettings& props);
		virtual void Shutdown();
		
	private:
		SDL_Window* m_Window;
		RendererContext* m_RendererContext;
		
		struct WindowData
		{
			const char* title;
			u32 width;
			u32 height;

			u32 windowID;
			u32 windowFlags;

			EventCallbackFunction eventCallback;
		};

		WindowData m_Data;
	};
}
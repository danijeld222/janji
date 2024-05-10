#pragma once

#include "WindowBase.h"

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

		inline virtual void* GetNativeWindow() const override { return m_Window; }
		
		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.eventCallback = callback; }
		
		static int HandleWindowResizeEvent(void* data, SDL_Event* e);
		static int HandleWindowCloseEvent(void* data, SDL_Event* e);
		static int HandleKeyboardEvent(void* data, SDL_Event* e);
		static int HandleMouseButtonEvent(void* data, SDL_Event* e);
		static int HandleMouseScrollEvent(void* data, SDL_Event* e);
		static int HandleMouseMoveEvent(void* data, SDL_Event* e);
		
	private:
		virtual void Initialize(const WindowSettings& props);
		virtual void Shutdown();
		
	private:
		SDL_Window* m_Window;
		
		// Temporary
		//Renderer* m_Renderer;
		
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
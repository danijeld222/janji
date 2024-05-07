#pragma once

#include "WindowBase.h"

#include "Core/Renderer/Renderer.h"

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
		
		inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.eventCallback = callback; }
	
	private:
		virtual void Initialize(const WindowSettings& props);
		virtual void Shutdown();
		
	private:
		SDL_Window* m_Window;
		
		// Temporary
		Renderer* m_Renderer;
		//Events* m_Events;

		struct WindowData
		{
			const char* title;
			u32 width;
			u32 height;
			u32 windowFlags;

			EventCallbackFunction eventCallback;
		};

		WindowData m_Data;
	};
}
#include "Window.h"
#include "Core/Asserts.h"

#include <stdio.h>

namespace Core 
{
	static bool s_SDLInitialized = false;

	WindowBase* WindowBase::Create(const WindowSettings& settings)
	{
		return new Window(settings);
	}

	Window::Window(const WindowSettings& settings)
	{
		Initialize(settings);
	}

	Window::~Window()
	{
		Shutdown();
	}

	void Window::Initialize(const WindowSettings& settings)
	{
		m_Data.title = settings.title;
		m_Data.width = settings.width;
		m_Data.height = settings.height;
		m_Data.windowFlags = settings.windowFlags;

		if (!s_SDLInitialized)
		{
			u32 result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);
			COREASSERT_MESSAGE(!result, SDL_GetError());
			
			s_SDLInitialized = true;
		}

		m_Window = SDL_CreateWindow(m_Data.title, m_Data.width, m_Data.height, m_Data.windowFlags);

		COREASSERT_MESSAGE(m_Window, SDL_GetError());

		SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		SDL_ShowWindow(m_Window);

		m_Renderer = new Renderer(m_Window, SDL_RENDERER_PRESENTVSYNC);
		//m_Events = new Events();
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Window::OnUpdate()
	{
		//glfwPollEvents();
		//glfwSwapBuffers(m_Window);
		m_Renderer->Run(m_Window);
	}
}
#include "Window.h"
#include "Core/Asserts.h"
#include "Core/Logger/Logger.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"

#include <stdio.h>

#include <SDL3/SDL_events.h>

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
		//m_Data.windowFlags = settings.windowFlags;
		m_Data.windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;

		if (!s_SDLInitialized)
		{
			u32 result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);
			COREASSERT_MESSAGE(!result, SDL_GetError());
			
			const char* glsl_version = "#version 150";
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
			
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
			
			s_SDLInitialized = true;
		}
		
		m_Window = SDL_CreateWindow(m_Data.title, m_Data.width, m_Data.height, m_Data.windowFlags);
		
		COREASSERT_MESSAGE(m_Window, SDL_GetError());
		
		m_Data.windowID = SDL_GetWindowID(m_Window);
		
		m_RendererContext = new RendererContext(m_Window, SDL_RENDERER_PRESENTVSYNC);
		
		SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		//SDL_ShowWindow(m_Window);

		SDL_AddEventWatch(HandleWindowResizeEvent, &m_Data);
		SDL_AddEventWatch(HandleWindowCloseEvent, &m_Data);
		SDL_AddEventWatch(HandleKeyboardEvent, &m_Data);
		SDL_AddEventWatch(HandleMouseButtonEvent, &m_Data);
		SDL_AddEventWatch(HandleMouseScrollEvent, &m_Data);
		SDL_AddEventWatch(HandleMouseMoveEvent, &m_Data);
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(m_Window);
		SDL_Quit();
	}

	void Window::OnUpdate()
	{
		SDL_Event m_Event;
		while (SDL_PollEvent(&m_Event))
		{
			GenericSDL_Event event(&m_Event);
			m_Data.eventCallback(event);
		}

		m_RendererContext->SwapBuffers();
	}
	
	i32 Window::HandleWindowResizeEvent(void* data, SDL_Event* e)
	{
		if (e->type == SDL_EVENT_WINDOW_RESIZED || e->type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
		{
			WindowData& windowData = *(WindowData*)data;
			
			WindowResizeEvent event(e->window.data1, e->window.data2);
			windowData.eventCallback(event);
			
			return 1;
		}
		
		return 0;
	}

	i32 Window::HandleWindowCloseEvent(void* data, SDL_Event* e)
	{
		WindowData& windowData = *(WindowData*)data;
		
		if (e->type == SDL_EVENT_QUIT || (e->type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && e->window.windowID == windowData.windowID))
		{
			WindowCloseEvent event;
			windowData.eventCallback(event);
			
			return 1;
		}
		
		return 0;
	}

	i32 Window::HandleKeyboardEvent(void* data, SDL_Event* e)
	{
		WindowData& windowData = *(WindowData*)data;
		
		if (e->type == SDL_EVENT_KEY_DOWN)
		{
			KeyPressedEvent event(e->key.keysym.sym, e->key.repeat);
			windowData.eventCallback(event);
			
			return 0;
		}
		else if (e->type == SDL_EVENT_KEY_UP)
		{
			KeyReleasedEvent event(e->key.keysym.sym);
			windowData.eventCallback(event);
			
			return 0;
		}
		
		return 0;
	}

	i32 Window::HandleMouseButtonEvent(void* data, SDL_Event* e)
	{
		WindowData& windowData = *(WindowData*)data;
		
		if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
		{
			MouseButtonPressedEvent event(e->button.button);
			windowData.eventCallback(event);
			
			return 1;
		}
		else if (e->type == SDL_EVENT_MOUSE_BUTTON_UP)
		{
			MouseButtonReleasedEvent event(e->button.button);
			windowData.eventCallback(event);
			
			return 1;
		}
		
		return 0;
	}

	i32 Window::HandleMouseScrollEvent(void* data, SDL_Event* e)
	{
		WindowData& windowData = *(WindowData*)data;
		
		if (e->type == SDL_EVENT_MOUSE_WHEEL)
		{
			MouseScrolledEvent event(e->wheel.x, e->wheel.y);
			windowData.eventCallback(event);
			
			return 1;
		}
		
		return 0;
	}

	i32 Window::HandleMouseMoveEvent(void* data, SDL_Event* e)
	{
		if (e->type == SDL_EVENT_MOUSE_MOTION)
		{
			WindowData& windowData = *(WindowData*)data;
			
			MouseMovedEvent event(e->motion.x, e->motion.y);
			windowData.eventCallback(event);
			
			return 0;
		}
		
		return 0;
	}
}
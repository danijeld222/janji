#pragma once

#ifdef _MSC_VER
	#pragma warning (disable: 5105)             // https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105?view=msvc-160
#endif

#include "Core/Defines.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <stdio.h>
#include <SDL3/SDL.h>

namespace Core
{
	class RendererContext
	{
	public:
		RendererContext(SDL_Window* window, u32 rendererFlags);
		~RendererContext();
		
		void SwapBuffers();
		SDL_GLContext GetOpenGLContext();
		
	private:
		SDL_Window* m_Window;
		SDL_GLContext m_Context;
		SDL_Surface* m_WindowSurface;
	};
}
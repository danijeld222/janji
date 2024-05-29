#pragma once

#ifdef _MSC_VER
#pragma warning (disable: 5105)             // https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105?view=msvc-160
#endif

#include "Core/Defines.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <stdio.h>
#include <SDL3/SDL.h>

namespace Core
{
    class Renderer
    {
    public:
        Renderer(SDL_Window* window, u32 rendererFlags);
        ~Renderer();
        
        void ClearScreen();
        void ClearScreen(u8 red, u8 green, u8 blue, u8 alpha);
        void SwapBuffers();
        void Update(SDL_Window* window);
        SDL_GLContext GetOpenGLContext();
    
    private:
        SDL_GLContext m_Context;
        SDL_Surface* m_WindowSurface;
    };
}
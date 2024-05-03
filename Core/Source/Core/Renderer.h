#pragma once

#ifdef _MSC_VER
#pragma warning (disable: 5105)             // https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5105?view=msvc-160
#endif

#include "Defines.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <stdio.h>
#include <SDL3/SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL3/SDL_opengles2.h>
#else
#include <SDL3/SDL_opengl.h>
#endif

class Renderer
{
public:
    Renderer(SDL_Window* Window, u32 RendererFlags);
    ~Renderer();
    
    void ClearScreen(i32 r, i32 g, i32 b, i32 a);
    void Update();
    void Render();

    SDL_Renderer* GetRenderer();

private:
    SDL_Renderer* pRenderer;
};
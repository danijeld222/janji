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

        void ClearScreen(u8 red, u8 green, u8 blue, u8 alpha);
        void Update(SDL_Window* window);
        void Render();
        void Run(SDL_Window* window);

        void SetPixel(SDL_Surface* surface, int x, int y, u32 pixel);
        void RenderDebugGradient(i32 xOffset, i32 yOffset);

        SDL_Renderer* GetRenderer();

    private:
        SDL_Renderer* m_Renderer;
        SDL_Surface* m_Surface;

        SDL_Surface* m_DebugSurface;
        SDL_Texture* m_DebugTexture;
        SDL_Palette* m_DebugPalette;
        SDL_FRect* m_DebugTextureRect;

        i32 m_DebugXOffset = 0;
        i32 m_DebugYOffset = 0;

        u8* m_BitmapMemory;
    };
}
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

class Renderer
{
public:
    Renderer(SDL_Window* Window, u32 RendererFlags);
    ~Renderer();
    
    void ClearScreen(u8 Red, u8 Green, u8 Blue, u8 Alpha);
    void Update(SDL_Window* Window);
    void Render();
    
    void SetPixel(SDL_Surface* Surface, int x, int y, u32 Pixel);
    void RenderDebugGradient(i32 XOffset, i32 YOffset);

    SDL_Renderer* GetRenderer();

private:
    SDL_Renderer* pRenderer;
    SDL_Surface* pSurface;

    SDL_Surface* pDebugSurface;
    SDL_Texture* pDebugTexture;
    SDL_Palette* DebugPalette;
    SDL_FRect* DebugTextureRect;

    i32 DebugXOffset = 0;
    i32 DebugYOffset = 0;

    u8* BitmapMemory;
};
#pragma once

#include "Defines.h"

#include <SDL3/SDL.h>

class Window
{
public:
    Window(const char* Title, i32 Width, i32 Height, SDL_WindowFlags WindowFlags);
    ~Window();

    SDL_Window* GetWindow();

private:
    SDL_Window* pWindow;
};
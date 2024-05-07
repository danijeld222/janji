#pragma once

#include "Defines.h"

#include <SDL3/SDL.h>

class Window
{
public:
    Window(const char* title, i32 width, i32 height, SDL_WindowFlags windowFlags);
    ~Window();

    SDL_Window* GetWindow();

private:
    SDL_Window* m_Window;
};
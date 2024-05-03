#include "Window.h"
#include "Asserts.h"

#include <stdio.h>

Window::Window(const char* Title, i32 Width, i32 Height, SDL_WindowFlags WindowFlags)
{
    pWindow = SDL_CreateWindow(Title, Width, Height, WindowFlags);

    COREASSERT_MESSAGE(pWindow, SDL_GetError());
    
    SDL_SetWindowPosition(pWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(pWindow);
}

Window::~Window()
{
    SDL_DestroyWindow(pWindow);
}

SDL_Window* Window::GetWindow()
{
    return pWindow;
}

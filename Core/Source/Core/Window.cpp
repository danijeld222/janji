#include "Window.h"
#include "Asserts.h"

#include <stdio.h>

Window::Window(const char* title, i32 width, i32 height, SDL_WindowFlags windowFlags)
{
    m_Window = SDL_CreateWindow(title, width, height, windowFlags);

    COREASSERT_MESSAGE(m_Window, SDL_GetError());
    
    SDL_SetWindowPosition(m_Window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    SDL_ShowWindow(m_Window);
}

Window::~Window()
{
    SDL_DestroyWindow(m_Window);
}

SDL_Window* Window::GetWindow()
{
    return m_Window;
}

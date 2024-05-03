#include "Application.h"
#include "Asserts.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include "imgui_impl_sdl3.h"

Application::Application(u32 SDLFlags)
{
    u32 Result = SDL_Init(SDLFlags);

    COREASSERT_MESSAGE(!Result, SDL_GetError());
}

Application::~Application()
{
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}
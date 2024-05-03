#include "Events.h"
#include "Asserts.h"

#include "imgui_impl_sdl3.h"

bool Events::HandleEvents(SDL_Window* Window)
{
    COREASSERT_MESSAGE(Window, "Events - Window is not valid.");

    while (SDL_PollEvent(&Event))
    {
        ImGui_ImplSDL3_ProcessEvent(&Event);

        if (Event.type == SDL_EVENT_QUIT)
        {
            return false;
        }
        if (Event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && Event.window.windowID == SDL_GetWindowID(Window))
        {
            return false;
        }
    }
    return true;
}
#include "Events.h"
#include "Core/Asserts.h"

#include "imgui_impl_sdl3.h"

namespace Core
{
    b8 Events::HandleEvents(SDL_Window* window)
    {
        COREASSERT_MESSAGE(window, "Events - Window is not valid.");

        while (SDL_PollEvent(&m_Event))
        {
            ImGui_ImplSDL3_ProcessEvent(&m_Event);

            if (m_Event.type == SDL_EVENT_QUIT)
            {
                return false;
            }
            if (m_Event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && m_Event.window.windowID == SDL_GetWindowID(window))
            {
                return false;
            }
        }
        return true;
    }
}
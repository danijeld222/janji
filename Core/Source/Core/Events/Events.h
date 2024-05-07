#pragma once

#include "Core/Defines.h"
#include <SDL3/SDL.h>

namespace Core
{
    class Events
    {
    public:
        b8 HandleEvents(SDL_Window* window);
        
    private:
        SDL_Event m_Event;
    };
}
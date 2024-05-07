#pragma once

#include "Defines.h"
#include <SDL3/SDL.h>

class Events
{
public:
    bool HandleEvents(SDL_Window* window);

private:
    SDL_Event m_Event;
};
#pragma once

#include "Defines.h"
#include <SDL3/SDL.h>

class Events
{
public:
    bool HandleEvents(SDL_Window* Window);

private:
    SDL_Event Event;
};
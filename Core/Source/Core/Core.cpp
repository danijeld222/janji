#include <stdio.h>
#include <SDL3/SDL.h>

#include "Core.h"
#include "Defines.h"

#include "Application.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"

int TestingRestructure()
{
    Application* _Application = new Application(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);

    u32 WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    Window* _Window = new Window("Janji", 1280, 720, WindowFlags);
    Renderer* _Renderer = new Renderer(_Window->GetWindow(), SDL_RENDERER_PRESENTVSYNC);
    Events* _Events = new Events();

    while (_Events->HandleEvents(_Window->GetWindow()))
    {
        _Renderer->ClearScreen(128, 128, 128, 255);
        _Renderer->Render();
        _Renderer->Update();
    }

    return 0;
}
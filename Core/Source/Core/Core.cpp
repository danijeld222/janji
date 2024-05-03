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

    u8 RedChannel = 0;
    u8 GreenChannel = 85;
    u8 BlueChannel = 170;
    u8 AlphaChannel = 255;

    while (_Events->HandleEvents(_Window->GetWindow()))
    {
        _Renderer->ClearScreen(RedChannel, GreenChannel, BlueChannel, AlphaChannel);
        _Renderer->Update(_Window->GetWindow());
        _Renderer->Render();

        RedChannel++;
        GreenChannel++;
        BlueChannel++;
    }

    return 0;
}
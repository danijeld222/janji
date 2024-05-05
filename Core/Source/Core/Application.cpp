#include "Application.h"
#include "Asserts.h"
#include "Logger.h"
#include "GameType.h"
#include "CoreMemory.h"

#include <SDL3/SDL.h>
#include <stdio.h>
#include "imgui_impl_sdl3.h"

Application::Application(Game* GameInstance, u32 SDLFlags)
{
    COREASSERT_MESSAGE(!Initialized, "Application is already created");
    
    AppState.GameInstance = GameInstance;
    
    // We should initialize logging and future subsystems
    // 
    
    u32 Result = SDL_Init(SDLFlags);
    
    COREASSERT_MESSAGE(!Result, SDL_GetError());
    
    // Initialization of Application necessary components
    u32 WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    _Window = new Window("Janji", 1280, 720, WindowFlags);
    _Renderer = new Renderer(_Window->GetWindow(), SDL_RENDERER_PRESENTVSYNC);
    _Events = new Events();

    AppState.IsRunning = true;
    AppState.IsSuspended = false;

    // In future if we want to handle platforms specific things we should set it up here

    if (!AppState.GameInstance->Initialize(AppState.GameInstance))
    {
        // Force Assert if game initialization failed
        COREASSERT_MESSAGE(false, "Game failed to Initialize");
    }

    AppState.GameInstance->OnResize(AppState.GameInstance, AppState.Width, AppState.Height);

    Initialized = true;
}

Application::~Application()
{
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_Quit();
}

b8 Application::ApplicationRun()
{
    COREINFO(GetMemoryUsage());
    
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

    return true;
}
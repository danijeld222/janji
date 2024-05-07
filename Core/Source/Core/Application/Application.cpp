#include "Application.h"
#include "Core/Asserts.h"
#include "Core/Logger/Logger.h"
#include "Core/CoreMemory.h"
#include "Core/Events/ApplicationEvent.h"

/*
#include <SDL3/SDL.h>
#include <stdio.h>
#include "imgui_impl_sdl3.h"

Application::Application(Game* gameInstance, u32 SDLFlags)
{
    COREASSERT_MESSAGE(!m_Initialized, "Application is already created");
    
    m_AppState.gameInstance = gameInstance;
    
    // We should initialize logging and future subsystems
    // 
    
    u32 result = SDL_Init(SDLFlags);
    
    COREASSERT_MESSAGE(!result, SDL_GetError());
    
    // Initialization of Application necessary components
    u32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN;
    m_Window = new Window("Janji", 1280, 720, windowFlags);
    m_Renderer = new Renderer(m_Window->GetWindow(), SDL_RENDERER_PRESENTVSYNC);
    m_Events = new Events();

    m_AppState.isRunning = true;
    m_AppState.isSuspended = false;

    // In future if we want to handle platforms specific things we should set it up here

    if (!m_AppState.gameInstance->initialize(m_AppState.gameInstance))
    {
        // Force Assert if game initialization failed
        COREASSERT_MESSAGE(false, "Game failed to Initialize");
    }

    m_AppState.gameInstance->onResize(m_AppState.gameInstance, m_AppState.width, m_AppState.height);

    m_Initialized = true;
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
    
    WindowResizeEvent event(1280, 720);
    if (event.IsInCategory(EventCategoryApplication))
    {
        COREINFO(event.GetName());
    }
    
    u8 redChannel = 0;
    u8 greenChannel = 85;
    u8 blueChannel = 170;
    u8 alphaChannel = 255;

    while (m_Events->HandleEvents(m_Window->GetWindow()))
    {
        m_Renderer->ClearScreen(redChannel, greenChannel, blueChannel, alphaChannel);
        m_Renderer->Update(m_Window->GetWindow());
        m_Renderer->Render();

        redChannel++;
        greenChannel++;
        blueChannel++;
    }

    return true;
}

*/

namespace Core {
    
    Application::Application()
    {
        InitializeMemoryStats();
        Core::Logger::Initialize();
        
        m_Window = WindowBase::Create();
        
        m_Running = true;
    }
    
    Application::~Application()
    {
        ShutdownMemoryStats();
    }
    
    void Application::ApplicationRun()
    {
        COREINFO(GetMemoryUsage());
        
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }
    
}
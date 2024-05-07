#pragma once

#include "Defines.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "GameType.h"

struct ApplicationState 
{
    Game* gameInstance;
    b8 isRunning;
    b8 isSuspended;
    i16 width;
    i16 height;
    f64 lastTime;
};

class Application 
{
public:
    Application(Game* gameInstance, u32 SDLFlags);
    ~Application();
    
    b8 ApplicationRun();
    
private:
    Window* m_Window;
    Renderer* m_Renderer;
    Events* m_Events;
    
private:
    b8 m_Initialized = false;
    ApplicationState m_AppState;
};
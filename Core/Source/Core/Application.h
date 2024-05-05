#pragma once

#include "Defines.h"
#include "Window.h"
#include "Renderer.h"
#include "Events.h"
#include "GameType.h"

struct ApplicationState 
{
    Game* GameInstance;
    b8 IsRunning;
    b8 IsSuspended;
    i16 Width;
    i16 Height;
    f64 LastTime;
};

class Application 
{
public:
    Application(Game* GameInstance, u32 SDLFlags);
    ~Application();
    
    COREAPI b8 ApplicationRun();
    
private:
    Window* _Window;
    Renderer* _Renderer;
    Events* _Events;
    
private:
    b8 Initialized = false;
    ApplicationState AppState;
};
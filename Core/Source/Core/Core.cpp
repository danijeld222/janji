#include <stdio.h>
#include <SDL3/SDL.h>

#include "Core.h"
#include "Defines.h"
#include "Asserts.h"
#include "Application.h"

#include "CoreMemory.h"
#include "Logger.h"

int CoreMain()
{
    InitializeMemoryStats();
    InitializeLogging();
    
    if (!CreateGame)
    {
        COREFATAL("Create Game function is not binded");
        
        return -1;
    }
    
    Game GameInstance;
    if (!CreateGame(&GameInstance))
    {
        COREFATAL("Could not create game");
        
        return -2;
    }
    
    // Check for Game Instance function pointer bindings
    if (!GameInstance.Initialize || !GameInstance.Update || !GameInstance.Render || !GameInstance.OnResize)
    {
        COREFATAL("Game Instance function pointer binding failed");
        
        return -3;
    }
    
    Application* _Application = new Application(&GameInstance, SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);
    COREASSERT_MESSAGE(_Application, "Application failed to initialize");
    
    // Start game loop
    if (!_Application->ApplicationRun())
    {
        return 1;
    }
    
    ShutdownLogging();
    ShutdownMemoryStats();
    
    return 0;
}
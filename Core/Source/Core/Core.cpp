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
    
    if (!createGame)
    {
        COREFATAL("Create Game function is not binded");
        
        return -1;
    }
    
    Game gameInstance;
    if (!createGame(&gameInstance))
    {
        COREFATAL("Could not create game");
        
        return -2;
    }
    
    // Check for Game Instance function pointer bindings
    if (!gameInstance.initialize || !gameInstance.update || !gameInstance.render || !gameInstance.onResize)
    {
        COREFATAL("Game Instance function pointer binding failed");
        
        return -3;
    }
    
    Application* application = new Application(&gameInstance, SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);
    COREASSERT_MESSAGE(application, "Application failed to initialize");
    
    // Start game loop
    if (!application->ApplicationRun())
    {
        return 1;
    }
    
    ShutdownLogging();
    ShutdownMemoryStats();
    
    return 0;
}
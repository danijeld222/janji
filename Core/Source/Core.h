#pragma once

#include "Core/Application/Application.h"
#include "Core/Logger/Logger.h"
#include "Core/EntryPoint.h"


// First we should bind function with same signature in application then call CoreMain()
//COREAPI std::function<b8(Game* GameOut)> createGame;

// This is called from int main(void) of application binded to this dll
//COREAPI int CoreMain();

/*int CoreMain()
{
    InitializeMemoryStats();
    Core::Logger::Initialize();
    
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
    
    //Application* application = new Application(&gameInstance, SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMEPAD);
    //COREASSERT_MESSAGE(application, "Application failed to initialize");
    //
    //// Start game loop
    //if (!application->ApplicationRun())
    //{
    //    return 1;
    //}
    //

    ShutdownMemoryStats();
    
    return 0;
}*/
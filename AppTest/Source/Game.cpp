#include "Game.h"

#include <Core/Logger.h>
#include <Core/CoreMemory.h>

// Define the function to create a game
b8 CreateGameImplementation(Game* OutGame) {
    OutGame->AppConfig.Width = 1280;
    OutGame->AppConfig.Height = 720;
    OutGame->AppConfig.Name = (char*)"Janji";
    
    OutGame->Initialize = GameInitialize;
    OutGame->Update = GameUpdate;
    OutGame->Render = GameRender;
    OutGame->OnResize = GameOnResize;
    
    OutGame->State = CoreAllocate(sizeof(GameState), MEMORY_TAG_GAME);
    
    return true;
}

b8 GameInitialize(Game* GameInstance) 
{
    COREDEBUG("GameInitialize() called!");
    
    return true;
}

b8 GameUpdate(Game* GameInstance, f32 DeltaTime) 
{
    return true;
}

b8 GameRender(Game* GameInstance, f32 DeltaTime) 
{
    return true;
}

void GameOnResize(Game* GameInstance, u32 Width, u32 Height) 
{

}
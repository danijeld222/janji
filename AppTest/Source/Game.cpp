#include "Game.h"

#include <Core/Logger/Logger.h>
#include <Core/CoreMemory.h>

// Define the function to create a game
b8 CreateGameImplementation(Game* outGame) {
    outGame->appConfig.width = 1280;
    outGame->appConfig.height = 720;
    outGame->appConfig.name = (char*)"Janji";
    
    outGame->initialize = GameInitialize;
    outGame->update = GameUpdate;
    outGame->render = GameRender;
    outGame->onResize = GameOnResize;
    
    outGame->state = CoreAllocate(sizeof(GameState), MEMORY_TAG_GAME);
    
    return true;
}

b8 GameInitialize(Game* gameInstance) 
{
    return true;
}

b8 GameUpdate(Game* gameInstance, f32 deltaTime) 
{
    return true;
}

b8 GameRender(Game* gameInstance, f32 deltaTime) 
{
    return true;
}

void GameOnResize(Game* gameInstance, u32 width, u32 height) 
{

}
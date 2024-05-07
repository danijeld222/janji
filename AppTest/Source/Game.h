#pragma once

#include <Core/Defines.h>
#include <Core/GameType.h>

struct GameState
{
	f32 deltaTime;
};

b8 CreateGameImplementation(Game* outGame);

b8 GameInitialize(Game* gameInstance);

b8 GameUpdate(Game* gameInstance, f32 deltaTime);

b8 GameRender(Game* gameInstance, f32 deltaTime);

void GameOnResize(Game* gameInstance, u32 width, u32 height);
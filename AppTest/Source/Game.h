#pragma once

#include <Defines.h>
#include <GameType.h>

struct GameState
{
	f32 DeltaTime;
};

b8 CreateGameImplementation(Game* OutGame);

b8 GameInitialize(Game* GameInstance);

b8 GameUpdate(Game* GameInstance, f32 DeltaTime);

b8 GameRender(Game* GameInstance, f32 DeltaTime);

void GameOnResize(Game* GameInstance, u32 Width, u32 Height);
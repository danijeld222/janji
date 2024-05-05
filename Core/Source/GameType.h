#pragma once

#include "Defines.h"

#include <functional>

struct ApplicationConfig
{
    i16 Width;
    i16 Height;
    char* Name;
};

struct Game
{
    ApplicationConfig AppConfig;
    
    std::function<b8(Game* GameInstance)> Initialize;
    std::function<b8(Game* GameInstance, f32 DeltaTime)> Update;
    std::function<b8(Game* GameInstance, f32 DeltaTime)> Render;
    std::function<void(Game* GameInstance, u32 Width, u32 Height)> OnResize;
    
    f32 DeltaTime;
};
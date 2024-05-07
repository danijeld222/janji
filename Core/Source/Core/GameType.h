#pragma once

#include "Defines.h"

#include <functional>

struct ApplicationConfig
{
    i16 width;
    i16 height;
    char* name;
};

struct Game
{
    ApplicationConfig appConfig;
    
    std::function<b8(Game* gameInstance)> initialize;
    std::function<b8(Game* gameInstance, f32 deltaTime)> update;
    std::function<b8(Game* gameInstance, f32 deltaTime)> render;
    std::function<void(Game* gameInstance, u32 width, u32 height)> onResize;
    
    void* state;
};
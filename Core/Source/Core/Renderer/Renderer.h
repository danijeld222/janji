#pragma once

#include "Core/Renderer/RendererCommands.h"

#include "Core/Defines.h"

namespace Core
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();
        
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
    };
}
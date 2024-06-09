#pragma once

#include "Core/Defines.h"
#include "Core/Renderer/RendererCommands.h"
#include "Core/Renderer/Camera.h"
#include "Core/Renderer/Shader.h"

namespace Core
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        
        static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
        
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}
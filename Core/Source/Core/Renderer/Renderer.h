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
        
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
        
    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };
}
#pragma once

#include "Core/Defines.h"
#include "Core/Renderer/RendererCommands.h"
#include "Core/Renderer/Camera.h"
#include "Core/Renderer/Shader.h"

#include "Core/Renderer/Texture.h"

namespace Core
{
    class Renderer
    {
    public:
        static void Init();
        static void Shutdown();
        static void OnWindowResize(u32 width, u32 height);
        
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
    
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();
        
        static void BeginScene(const OrthographicCamera& camera);
        static void EndScene();
        
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
        
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color, const Ref<Texture2D>& texture);
    };
}
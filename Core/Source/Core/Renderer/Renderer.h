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
        static void Flush();
        
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
        
        static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, f32 rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, f32 rotation, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, f32 rotation, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, f32 rotation, const Ref<Texture2D>& texture, f32 tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
        
        // Stats
        struct Statistics
        {
            u32 DrawCalls = 0;
            u32 QuadCount = 0;
            
            u32 GetTotalVertexCount() { return QuadCount * 4; }
            u32 GetTotalIndexCount() { return QuadCount * 6; }
        };
        
        static void ResetStats();
        static Statistics GetStats();
        
    private:
        static void FlushAndReset();
    };
}
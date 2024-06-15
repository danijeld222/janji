#include <Core.h>
#include <Core/Events/MouseEvent.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

class TestingLayer : public Core::Layer
{
public:
    TestingLayer()
        : Layer("Testing"),
          m_Camera(-1.28f, 1.28f, -0.72f, 0.72f),
          m_CameraPosition(0.0f)
    {
        m_VertexArray.reset(new Core::VertexArray());
        
        f32 vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };

        Core::Ref<Core::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(new Core::VertexBuffer(vertices, sizeof(vertices)));
        Core::BufferLayout layout = {
            { Core::ShaderDataType::Float3, "a_Position" },
            { Core::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);
        
        u32 indices[3] = { 0, 1, 2 };
        Core::Ref<Core::IndexBuffer> indexBuffer;
        indexBuffer.reset(new Core::IndexBuffer(indices, sizeof(indices) / sizeof(u32)));
        m_VertexArray->SetIndexBuffer(indexBuffer);
        
        m_SquareVertexArray.reset(new Core::VertexArray());
        
        f32 squareVertices[5 * 4] = {
             -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
              0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
              0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        
        Core::Ref<Core::VertexBuffer> squareVB;
        squareVB.reset(new Core::VertexBuffer(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { Core::ShaderDataType::Float3, "a_Position" },
            { Core::ShaderDataType::Float2, "a_TexCoord" }
            });
        m_SquareVertexArray->AddVertexBuffer(squareVB);
        
        u32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Core::Ref<Core::IndexBuffer> squareIB;
        squareIB.reset(new Core::IndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(u32)));
        m_SquareVertexArray->SetIndexBuffer(squareIB);
        
        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            out vec3 v_Position;
            out vec4 v_Color;
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
            }
        )";
        
        std::string fragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            in vec4 v_Color;
            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }
        )";
        
        m_Shader = Core::Shader::CreateWithSource("VertexPosColor", vertexSrc, fragmentSrc);
        
        std::string solidColorShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;
            
            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
            }
        )";
        
        std::string solidColorShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;
            
            in vec3 v_Position;
            
            uniform vec3 u_Color;
            
            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";
        
        m_SolidColorShader = Core::Shader::CreateWithSource("SolidColor", solidColorShaderVertexSrc, solidColorShaderFragmentSrc);
        
        m_ShaderLibrary.Load("Texture", "Assets/Shaders/Texture.glsl");
        //m_ShaderLibrary.Load("Texture", "Assets/Shaders/TextureVertex.glsl", "Assets/Shaders/TextureFragment.glsl");
        
        m_Texture = std::make_shared<Core::Texture2D>("Assets/Texture/WhatHappened.png");
        m_TextureWolf = std::make_shared<Core::Texture2D>("Assets/Texture/Wolf.png");
        
        m_ShaderLibrary.Get("Texture")->Bind();
        m_ShaderLibrary.Get("Texture")->UploadUniformInt("u_Texture", 0);
    }
    
    void OnUpdate(Core::Timestep timestep) override
    {
        if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_LEFT) || Core::InputBase::IsKeyPressed(SDL_SCANCODE_A))
        {
            m_CameraPosition.x -= m_CameraMoveSpeed * timestep;
        }
        else if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_RIGHT) || Core::InputBase::IsKeyPressed(SDL_SCANCODE_D))
        {
            m_CameraPosition.x += m_CameraMoveSpeed * timestep;
        }
        
        if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_UP) || Core::InputBase::IsKeyPressed(SDL_SCANCODE_W))
        {
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        }
        else if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_DOWN) || Core::InputBase::IsKeyPressed(SDL_SCANCODE_S))
        {
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
        }
        
        if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_UP) || Core::InputBase::IsKeyPressed(SDL_SCANCODE_W))
        {
            m_CameraPosition.y += m_CameraMoveSpeed * timestep;
        }
        else if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_DOWN) || Core::InputBase::IsKeyPressed(SDL_SCANCODE_S))
        {
            m_CameraPosition.y -= m_CameraMoveSpeed * timestep;
        }
        
        if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_Q))
        {
            m_CameraRotation += m_CameraRotationSpeed * timestep;
        }
        if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_E))
        {
            m_CameraRotation -= m_CameraRotationSpeed * timestep;
        }
        
        Core::RendererCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Core::RendererCommands::Clear();
        
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
        m_Camera.SetZoom(m_CameraZoom);
        
        Core::Renderer::BeginScene(m_Camera);
        
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
        
        m_SolidColorShader->Bind();
        m_SolidColorShader->UploadUniformFloat3("u_Color", m_SolidColor);
        
        for (int y = -10; y < 10; y++)
        {
            for (int x = -10; x < 10; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Core::Renderer::Submit(m_SolidColorShader, m_SquareVertexArray, transform);
            }
        }
        
        m_Texture->Bind();
        Core::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
        
        m_TextureWolf->Bind();
        Core::Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
        
        //Core::Renderer::Submit(m_Shader, m_VertexArray);
        
        Core::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SolidColor));
        ImGui::End();
    }
    
    void OnEvent(Core::Event& event) override
    {
        if (event.GetEventType() == Core::EventType::MouseScrolled)
        {
            Core::MouseScrolledEvent& scrollEvent = dynamic_cast<Core::MouseScrolledEvent&>(event);
            m_CameraZoom += m_CameraZoomAmount * scrollEvent.GetYOffset() * -1.0f;
        }
    }

private:
    Core::ShaderLibrary m_ShaderLibrary;
    
    Core::Ref<Core::Shader> m_Shader;
    Core::Ref<Core::VertexArray> m_VertexArray;
    
    Core::Ref<Core::Shader> m_SolidColorShader;
    Core::Ref<Core::VertexArray> m_SquareVertexArray;
    
    Core::Ref<Core::Texture2D> m_Texture;
    Core::Ref<Core::Texture2D> m_TextureWolf;
    
    Core::OrthographicCamera m_Camera;
    
    glm::vec3 m_SolidColor = { 0.2f, 0.3f, 0.8f };
    
    glm::vec3 m_CameraPosition;
    f32 m_CameraMoveSpeed = 2.0f;
    
    f32 m_CameraRotation = 0.0f;
    f32 m_CameraRotationSpeed = 180.0f;
    
    f32 m_CameraZoom = 1.0f;
    f32 m_CameraZoomAmount = 0.1f;
};

class Sandbox : public Core::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestingLayer());
    }
    
    ~Sandbox()
    {
    }
};

Core::Application* Core::CreateApplication()
{
    return new Sandbox();
}
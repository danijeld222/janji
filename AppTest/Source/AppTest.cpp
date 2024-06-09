#include <Core.h>
#include <Core/Events/MouseEvent.h>
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

        std::shared_ptr<Core::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(new Core::VertexBuffer(vertices, sizeof(vertices)));
        Core::BufferLayout layout = {
            { Core::ShaderDataType::Float3, "a_Position" },
            { Core::ShaderDataType::Float4, "a_Color" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);
        
        u32 indices[3] = { 0, 1, 2 };
        std::shared_ptr<Core::IndexBuffer> indexBuffer;
        indexBuffer.reset(new Core::IndexBuffer(indices, sizeof(indices) / sizeof(u32)));
        m_VertexArray->SetIndexBuffer(indexBuffer);
        
        m_SquareVA.reset(new Core::VertexArray());
        
        f32 squareVertices[3 * 4] = {
             -0.75f, -0.75f, 0.0f,
              0.75f, -0.75f, 0.0f,
              0.75f,  0.75f, 0.0f,
             -0.75f,  0.75f, 0.0f
        };
        
        std::shared_ptr<Core::VertexBuffer> squareVB;
        squareVB.reset(new Core::VertexBuffer(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { Core::ShaderDataType::Float3, "a_Position" }
            });
        m_SquareVA->AddVertexBuffer(squareVB);
        
        u32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Core::IndexBuffer> squareIB;
        squareIB.reset(new Core::IndexBuffer(squareIndices, sizeof(squareIndices) / sizeof(u32)));
        m_SquareVA->SetIndexBuffer(squareIB);
        
        std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            uniform mat4 u_ViewProjection;
            
            out vec3 v_Position;
            out vec4 v_Color;
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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
        
        m_Shader.reset(new Core::Shader(vertexSrc, fragmentSrc));
        
        std::string blueShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjection;
            
            out vec3 v_Position;
            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
            }
        )";
        
        std::string blueShaderFragmentSrc = R"(
            #version 330 core
            
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            void main()
            {
                color = vec4(0.2, 0.3, 0.8, 1.0);
            }
        )";
        
        m_BlueShader.reset(new Core::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
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
        
        Core::Renderer::Submit(m_BlueShader, m_SquareVA);
        Core::Renderer::Submit(m_Shader, m_VertexArray);
        
        Core::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
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
    std::shared_ptr<Core::Shader> m_Shader;
    std::shared_ptr<Core::VertexArray> m_VertexArray;
    
    std::shared_ptr<Core::Shader> m_BlueShader;
    std::shared_ptr<Core::VertexArray> m_SquareVA;
    
    Core::OrthographicCamera m_Camera;
    
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
#include "TestingLayer.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TestingLayer::TestingLayer() : Layer("Testing"),
    m_CameraController(1280.0f / 720.0f)
{
    m_VertexArray = Core::VertexArray::Create();

    f32 vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
    };
    
    Core::Ref<Core::VertexBuffer> vertexBuffer = Core::VertexBuffer::Create(vertices, sizeof(vertices));
    vertexBuffer->SetLayout({
        { Core::ShaderDataType::Float3, "a_Position" },
        { Core::ShaderDataType::Float4, "a_Color" }
        });
    m_VertexArray->AddVertexBuffer(vertexBuffer);
    
    u32 indices[3] = { 0, 1, 2 };
    Core::Ref<Core::IndexBuffer> indexBuffer = Core::IndexBuffer::Create(indices, sizeof(indices) / sizeof(u32));
    m_VertexArray->SetIndexBuffer(indexBuffer);
    
    m_SquareVertexArray = Core::VertexArray::Create();
    
    f32 squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };
    
    Core::Ref<Core::VertexBuffer> squareVB = Core::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
    squareVB->SetLayout({
        { Core::ShaderDataType::Float3, "a_Position" },
        { Core::ShaderDataType::Float2, "a_TexCoord" }
        });
    m_SquareVertexArray->AddVertexBuffer(squareVB);
    
    u32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Core::Ref<Core::IndexBuffer> squareIB = Core::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(u32));
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
    m_ShaderLibrary.Get("Texture")->SetInt("u_Texture", 0);
}

void TestingLayer::OnAttach()
{
    
}

void TestingLayer::OnDetach()
{
    
}

void TestingLayer::OnUpdate(Core::Timestep timestep)
{
    m_CameraController.OnUpdate(timestep);
    
    Core::RendererCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Core::RendererCommands::Clear();
    
    Core::Renderer::BeginScene(m_CameraController.GetCamera());
    
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    
    m_SolidColorShader->Bind();
    m_SolidColorShader->SetFloat3("u_Color", m_SolidColor);
    
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

void TestingLayer::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SolidColor));
    ImGui::End();
}

void TestingLayer::OnEvent(Core::Event& event)
{
    m_CameraController.OnEvent(event);
}
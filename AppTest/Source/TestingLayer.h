#pragma once

#include <Core.h>

class TestingLayer : public Core::Layer
{
	
public:
    TestingLayer();
    virtual ~TestingLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Core::Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Core::Event& e) override;

private:
    Core::ShaderLibrary m_ShaderLibrary;
    
    Core::Ref<Core::Shader> m_Shader;
    Core::Ref<Core::VertexArray> m_VertexArray;
    
    Core::Ref<Core::Shader> m_SolidColorShader;
    Core::Ref<Core::VertexArray> m_SquareVertexArray;
    
    Core::Ref<Core::Texture2D> m_Texture;
    Core::Ref<Core::Texture2D> m_TextureWolf;
    
    Core::OrthographicCameraController m_CameraController;
    
    glm::vec3 m_SolidColor = { 0.2f, 0.3f, 0.8f };
};
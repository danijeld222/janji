#pragma once

#include <Core.h>

class AppTest2D : public Core::Layer
{
public:
	AppTest2D();
	virtual ~AppTest2D() = default;
	
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	
	void OnUpdate(Core::Timestep timestep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Core::Event& event) override;
private:
	Core::OrthographicCameraController m_CameraController;
	
	Core::Ref<Core::VertexArray> m_SquareVA;
	Core::Ref<Core::Shader> m_FlatColorShader;
	
	glm::vec4 m_SolidColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
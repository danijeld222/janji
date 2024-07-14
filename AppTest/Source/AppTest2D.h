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
	
	Core::Ref<Core::Texture2D> m_CheckerboardTexture;
	Core::Ref<Core::Texture2D> m_WhatHappenedTexture;
	
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;

	glm::vec4 m_SolidColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
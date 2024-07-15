#include "AppTest2D.h"
#include "imgui.h"

#include "Core/Debug/Instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AppTest2D::AppTest2D()
	: Layer("AppTest2D"), 
	m_CameraController(1280.0f / 720.0f)
{
}

void AppTest2D::OnAttach()
{
	CORE_PROFILE_FUNCTION();
	
	m_CheckerboardTexture.reset(new Core::Texture2D("Assets/Texture/Checkerboard.png"));
	m_WhatHappenedTexture.reset(new Core::Texture2D("Assets/Texture/WhatHappened.png"));
}

void AppTest2D::OnDetach()
{
	CORE_PROFILE_FUNCTION();
}

void AppTest2D::OnUpdate(Core::Timestep timestep)
{
	CORE_PROFILE_FUNCTION();
	
	m_CameraController.OnUpdate(timestep);
	
	{
		CORE_PROFILE_SCOPE("Renderer Prep");
		
		Core::RendererCommands::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Core::RendererCommands::Clear();
	}
	
	{
		CORE_PROFILE_SCOPE("Renderer Draw");
		
		Core::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Core::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Core::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Core::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
		Core::Renderer2D::DrawQuad({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, m_SolidColor, m_WhatHappenedTexture);
		Core::Renderer2D::EndScene();
	}
}

void AppTest2D::OnImGuiRender()
{
	CORE_PROFILE_FUNCTION();
	
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SolidColor));
	ImGui::End();
}

void AppTest2D::OnEvent(Core::Event& event)
{
	m_CameraController.OnEvent(event);
}
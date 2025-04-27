#pragma once

#include "Core/Defines.h"

#include "Core/Renderer/Camera.h"
#include "Core/Time/Timestep.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

namespace Core
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(f32 aspectRatio, bool rotation = false);
		
		void OnUpdate(Timestep timestep);
		void OnEvent(Event& e);
		
		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
		
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		
	private:
		f32 m_AspectRatio;
		f32 m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;
		
		bool m_Rotation;
		
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		f32 m_CameraRotation = 0.0f;
		f32 m_CameraTranslationSpeed = 5.0f;
		f32 m_CameraRotationSpeed = 180.0f;
	};
}
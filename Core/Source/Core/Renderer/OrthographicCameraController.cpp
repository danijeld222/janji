#include "OrthographicCameraController.h"

#include "Core/Input/InputBase.h"

#include "Core/Debug/Instrumentor.h"

namespace Core
{
	OrthographicCameraController::OrthographicCameraController(f32 aspectRatio, b8 rotation)
		: m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
	{
	}
	
	void OrthographicCameraController::OnUpdate(Timestep timestep)
	{
		CORE_PROFILE_FUNCTION();
		
		if (InputBase::IsKeyPressed(SDL_SCANCODE_LEFT) || InputBase::IsKeyPressed(SDL_SCANCODE_A))
		{
			m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}
		else if (InputBase::IsKeyPressed(SDL_SCANCODE_RIGHT) || InputBase::IsKeyPressed(SDL_SCANCODE_D))
		{
			m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}
		
		if (InputBase::IsKeyPressed(SDL_SCANCODE_UP) || InputBase::IsKeyPressed(SDL_SCANCODE_W))
		{
			m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}
		else if (InputBase::IsKeyPressed(SDL_SCANCODE_DOWN) || InputBase::IsKeyPressed(SDL_SCANCODE_S))
		{
			m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
			m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * timestep;
		}
		
		if (m_Rotation)
		{
			if (InputBase::IsKeyPressed(SDL_SCANCODE_Q))
			{
				m_CameraRotation += m_CameraRotationSpeed * timestep;
			}
			if (InputBase::IsKeyPressed(SDL_SCANCODE_E))
			{
				m_CameraRotation -= m_CameraRotationSpeed * timestep;
			}

			if (m_CameraRotation > 180.0f)
			{
				m_CameraRotation -= 360.0f;
			}
			else if (m_CameraRotation <= -180.0f)
			{
				m_CameraRotation += 360.0f;
			}

			m_Camera.SetRotation(m_CameraRotation);
		}
		
		m_Camera.SetPosition(m_CameraPosition);
		
		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		CORE_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(CORE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(CORE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		CORE_PROFILE_FUNCTION();
		
		m_ZoomLevel -= e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		CORE_PROFILE_FUNCTION();
		
		m_AspectRatio = (f32)e.GetWidth() / (f32)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		
		return false;
	}
}
#pragma once

#include "Core/Defines.h"

#include <glm/glm.hpp>

namespace Core
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top);
		
		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);
		
		f32 GetRotation() const;
		void SetRotation(f32 rotation);
		
		f32 GetZoom() const;
		void SetZoom(f32 zoom);
		
		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetViewProjectionMatrix() const;
		
	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		f32 m_Rotation = 0.0f;
		f32 m_Zoom = 1.0f;
	};
}
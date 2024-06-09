#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Core
{
	OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
		  m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	
	const glm::vec3& OrthographicCamera::GetPosition() const 
	{
		return m_Position; 
	}
	
	void OrthographicCamera::SetPosition(const glm::vec3& position) 
	{
		m_Position = position; 
		
		RecalculateViewMatrix();
	}
	
	f32 OrthographicCamera::GetRotation() const 
	{
		return m_Rotation; 
	}
	
	void OrthographicCamera::SetRotation(f32 rotation) 
	{ 
		m_Rotation = rotation; 
		
		RecalculateViewMatrix();
	}
	
	f32 OrthographicCamera::GetScale() const
	{
		return m_Scale;
	}
	
	void OrthographicCamera::SetScale(f32 scale)
	{
		m_Scale = scale;
		
		RecalculateViewMatrix();
	}
	
	const glm::mat4& OrthographicCamera::GetProjectionMatrix() const
	{
		return m_ProjectionMatrix;
	}
	
	const glm::mat4& OrthographicCamera::GetViewMatrix() const
	{
		return m_ViewMatrix;
	}
	
	const glm::mat4& OrthographicCamera::GetViewProjectionMatrix() const
	{
		return m_ViewProjectionMatrix;
	}
	
	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 translate = glm::translate(glm::mat4{ 1.0f }, m_Position);
		glm::mat4 rotate = glm::rotate(glm::mat4{ 1.0f }, glm::radians(m_Rotation), glm::vec3{ 0.0f,0.0f,1.0f });
		glm::mat4 scale = glm::scale(glm::mat4{ 1.0f }, glm::vec3{ m_Scale, m_Scale, 1.0f });
		
		glm::mat4 transform = scale * rotate * translate;
		
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
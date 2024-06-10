#include "Renderer.h"

namespace Core
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	
	void Renderer::Init()
	{
		RendererCommands::Init();
	}
	
	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	
	void Renderer::EndScene()
	{
	}
	
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_Transform", transform);
		
		vertexArray->Bind();
		RendererCommands::DrawIndexed(vertexArray);
	}
}
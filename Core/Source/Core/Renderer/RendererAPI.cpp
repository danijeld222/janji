#include "RendererAPI.h"

#include "Core/Debug/Instrumentor.h"

#include <glad/gl.h>
#include "imgui.h"

namespace Core 
{
	Scope<RendererAPI> RendererAPI::Create()
	{
		return MakeScope<RendererAPI>();
	}
	
	void RendererAPI::Init()
	{
		CORE_PROFILE_FUNCTION();
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		glEnable(GL_DEPTH_TEST);
	}
	
	void RendererAPI::SetViewport(u32 x, u32 y, u32 width, u32 height)
	{
		CORE_PROFILE_FUNCTION();
		
		glViewport(x, y, width, height);
	}
	
	void RendererAPI::SetClearColor(const glm::vec4& color)
	{
		CORE_PROFILE_FUNCTION();
		
		glClearColor(color.r, color.g, color.b, color.a);
	}
	
	void RendererAPI::Clear()
	{
		CORE_PROFILE_FUNCTION();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	
	void RendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		CORE_PROFILE_FUNCTION();
		
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
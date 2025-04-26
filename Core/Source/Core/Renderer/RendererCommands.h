#pragma once

#include "Core/Renderer/RendererAPI.h"

namespace Core 
{
	class RendererCommands
	{
	public:
		static void Init()
		{
			s_RendererAPI->Init();
		}
		
		static void SetViewport(u32 x, u32 y, u32 width, u32 height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}
		
		static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		
		static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		static void DrawIndexed(const Ref<VertexArray>& vertexArray, u32 count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}
		
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}
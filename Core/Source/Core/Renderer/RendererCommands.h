#pragma once

#include "Core/Renderer/RendererAPI.h"

namespace Core 
{
	class RendererCommands
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		
		inline static void SetViewport(u32 x, u32 y, u32 width, u32 height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}
		
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
		
	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}
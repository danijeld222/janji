#pragma once

#include "Core/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Core 
{
	class RendererAPI
	{
	public:
		void Init();
		void SetViewport(u32 x, u32 y, u32 width, u32 height);
		
		void SetClearColor(const glm::vec4& color);
		void Clear();
		
		void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};
}
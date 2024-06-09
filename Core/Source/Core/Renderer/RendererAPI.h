#pragma once

#include "Core/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Core 
{
	class RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color);
		void Clear();
		
		void DrawIndexed(const Ref<VertexArray>& vertexArray);
	};
}
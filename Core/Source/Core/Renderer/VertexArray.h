#pragma once

#include "Core/Defines.h"
#include "Core/Renderer/Buffer.h"

#include <memory>
#include <vector>

namespace Core 
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		
		static Ref<VertexArray> Create();
		
		void Bind() const;
		void Unbind() const;
		
		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);
		
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
		
	private:
		u32 m_RendererID;
		u32 m_VertexBufferIndex = 0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
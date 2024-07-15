#include "Buffer.h"
#include "Renderer.h"

#include "Core/Debug/Instrumentor.h"

#include <glad/gl.h>

namespace Core
{
	void BufferLayout::CalculateOffsetAndStride()
	{
		u32 offset = 0;
		m_Stride = 0;
		
		for (BufferElement& element : m_Elements)
		{
			element.offset = offset;
			offset += element.size;
			m_Stride += element.size;
		}
	}
	
	// Vertex Buffer
	
	VertexBuffer::VertexBuffer(f32* vertices, u32 size)
	{
		CORE_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}
	
	VertexBuffer::~VertexBuffer()
	{
		CORE_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}
	
	Ref<VertexBuffer> VertexBuffer::Create(f32* vertices, u32 size)
	{
		return MakeRef<VertexBuffer>(vertices, size);
	}
	
	void VertexBuffer::Bind() const
	{
		CORE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	
	void VertexBuffer::Unbind() const
	{
		CORE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	const BufferLayout& VertexBuffer::GetLayout() const
	{
		return m_Layout;
	}
	
	void VertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}
	
	// Index Buffer
	
	IndexBuffer::IndexBuffer(u32* indices, u32 count)
		: m_Count(count)
	{
		CORE_PROFILE_FUNCTION();
		
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), indices, GL_STATIC_DRAW);
	}
	
	IndexBuffer::~IndexBuffer()
	{
		CORE_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}
	
	Ref<IndexBuffer> IndexBuffer::Create(u32* indices, u32 count)
	{
		return MakeRef<IndexBuffer>(indices, count);
	}
	
	void IndexBuffer::Bind() const
	{
		CORE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	
	void IndexBuffer::Unbind() const
	{
		CORE_PROFILE_FUNCTION();
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	u32 IndexBuffer::GetCount() const
	{ 
		return m_Count; 
	}
}
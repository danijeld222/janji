#include "VertexArray.h"

#include "Renderer.h"
#include "Core/Logger/Logger.h"
#include "Core/Asserts.h"

#include <glad/gl.h>

namespace Core
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Core::ShaderDataType::Float:
			return GL_FLOAT;
		case Core::ShaderDataType::Float2:
			return GL_FLOAT;
		case Core::ShaderDataType::Float3:
			return GL_FLOAT;
		case Core::ShaderDataType::Float4:
			return GL_FLOAT;
		case Core::ShaderDataType::Mat3:
			return GL_FLOAT;
		case Core::ShaderDataType::Mat4:
			return GL_FLOAT;
		case Core::ShaderDataType::Int:
			return GL_INT;
		case Core::ShaderDataType::Int2:
			return GL_INT;
		case Core::ShaderDataType::Int3:
			return GL_INT;
		case Core::ShaderDataType::Int4:
			return GL_INT;
		case Core::ShaderDataType::Bool:
			return GL_BOOL;
		}
		
		COREASSERT_MESSAGE(false, "Undefined Shader Data Type");
		
		return 0;
	}
	
	VertexArray::VertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	
	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	Ref<VertexArray> VertexArray::Create()
	{
		return std::make_shared<VertexArray>();
	}
	
	void VertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	
	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	
	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		COREASSERT_MESSAGE(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		u32 index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}
	
	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		
		m_IndexBuffer = indexBuffer;
	}
}
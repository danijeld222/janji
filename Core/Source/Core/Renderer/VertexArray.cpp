#include "VertexArray.h"

#include "Renderer.h"
#include "Core/Logger/Logger.h"
#include "Core/Asserts.h"

#include "Core/Debug/Instrumentor.h"

#include <glad/gl.h>

namespace Core
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:
			return GL_FLOAT;
		case ShaderDataType::Float2:
			return GL_FLOAT;
		case ShaderDataType::Float3:
			return GL_FLOAT;
		case ShaderDataType::Float4:
			return GL_FLOAT;
		case ShaderDataType::Mat3:
			return GL_FLOAT;
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
			return GL_INT;
		case ShaderDataType::Int2:
			return GL_INT;
		case ShaderDataType::Int3:
			return GL_INT;
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		}
		
		COREASSERT_MESSAGE(false, "Undefined Shader Data Type");
		
		return 0;
	}
	
	VertexArray::VertexArray()
	{
		CORE_PROFILE_FUNCTION();
		
		glCreateVertexArrays(1, &m_RendererID);
	}
	
	VertexArray::~VertexArray()
	{
		CORE_PROFILE_FUNCTION();
		
		glDeleteVertexArrays(1, &m_RendererID);
	}
	
	Ref<VertexArray> VertexArray::Create()
	{
		return std::make_shared<VertexArray>();
	}
	
	void VertexArray::Bind() const
	{
		CORE_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
	}
	
	void VertexArray::Unbind() const
	{
		CORE_PROFILE_FUNCTION();
		
		glBindVertexArray(0);
	}
	
	void VertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		CORE_PROFILE_FUNCTION();
		
		COREASSERT_MESSAGE(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();
		
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
			case ShaderDataType::Int:
			case ShaderDataType::Int2:
			case ShaderDataType::Int3:
			case ShaderDataType::Int4:
			case ShaderDataType::Bool:
			{
				glEnableVertexAttribArray(m_VertexBufferIndex);
				glVertexAttribPointer(m_VertexBufferIndex,
					element.GetComponentCount(),
					ShaderDataTypeToOpenGLBaseType(element.type),
					element.normalized ? GL_TRUE : GL_FALSE,
					layout.GetStride(),
					(const void*)element.offset);
				m_VertexBufferIndex++;
				break;
			}
			case ShaderDataType::Mat3:
			case ShaderDataType::Mat4:
			{
				uint8_t count = element.GetComponentCount();
				for (uint8_t i = 0; i < count; i++)
				{
					glEnableVertexAttribArray(m_VertexBufferIndex);
					glVertexAttribPointer(m_VertexBufferIndex,
						count,
						ShaderDataTypeToOpenGLBaseType(element.type),
						element.normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)(sizeof(float) * count * i));
					glVertexAttribDivisor(m_VertexBufferIndex, 1);
					m_VertexBufferIndex++;
				}
				break;
			}
			default:
				COREASSERT_MESSAGE(false, "Unknown ShaderDataType!");
			}
		}
		
		m_VertexBuffers.push_back(vertexBuffer);
	}
	
	void VertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		CORE_PROFILE_FUNCTION();
		
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
		
		m_IndexBuffer = indexBuffer;
	}
}
#pragma once

#include "Core/Defines.h"
#include "Core/Asserts.h"

#include <string>
#include <vector>

namespace Core
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};
	
	static u32 ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Core::ShaderDataType::Float:
			return 4;
		case Core::ShaderDataType::Float2:
			return 4 * 2;
		case Core::ShaderDataType::Float3:
			return 4 * 3;
		case Core::ShaderDataType::Float4:
			return 4 * 4;
		case Core::ShaderDataType::Mat3:
			return 4 * 3 * 3;
		case Core::ShaderDataType::Mat4:
			return 4 * 4 * 4;
		case Core::ShaderDataType::Int:
			return 4;
		case Core::ShaderDataType::Int2:
			return 4 * 2;
		case Core::ShaderDataType::Int3:
			return 4 * 3;
		case Core::ShaderDataType::Int4:
			return 4 * 4;
		case Core::ShaderDataType::Bool:
			return 1;
		}
		
		COREASSERT_MESSAGE(false, "Undefined Shader Data Type");
		
		return 0;
	}
	
	struct BufferElement
	{
		ShaderDataType type;
		std::string name;
		u32 size;
		size_t offset;
		b8 normalized;
		
		BufferElement() = default;
		
		BufferElement(ShaderDataType _type, const std::string& _name, b8 _normalized = false)
			: type(_type), name(_name), size(ShaderDataTypeSize(_type)), offset(0), normalized(_normalized)
		{
		}
		
		u32 GetComponentCount() const
		{
			switch (type)
			{
			case Core::ShaderDataType::Float:
				return 1;
			case Core::ShaderDataType::Float2:
				return 2;
			case Core::ShaderDataType::Float3:
				return 3;
			case Core::ShaderDataType::Float4:
				return 4;
			case Core::ShaderDataType::Mat3:
				return 3 * 3;
			case Core::ShaderDataType::Mat4:
				return 4 * 4;
			case Core::ShaderDataType::Int:
				return 1;
			case Core::ShaderDataType::Int2:
				return 2;
			case Core::ShaderDataType::Int3:
				return 3;
			case Core::ShaderDataType::Int4:
				return 4;
			case Core::ShaderDataType::Bool:
				return 1;
			}
			
			COREASSERT_MESSAGE(false, "Undefined Shader Data Type");
			
			return 0;
		}
	};
	
	class BufferLayout
	{
	public:
		BufferLayout() {}
		
		BufferLayout(const std::initializer_list<BufferElement>& elements) // https://en.cppreference.com/w/cpp/utility/initializer_list
			: m_Elements(elements)
		{
			CalculateOffsetAndStride();
		}
		
		inline u32 GetStride() const { return m_Stride; }
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		
		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	
	private:
		void CalculateOffsetAndStride();
	
	private:
		std::vector<BufferElement> m_Elements;
		u32 m_Stride = 0;
	};
	
	class VertexBuffer
	{
	public:
		VertexBuffer(u32 size);
		VertexBuffer(f32* vertices, u32 size);
		virtual ~VertexBuffer();
		
		void SetData(const void* data, u32 size);
		
		static Ref<VertexBuffer> Create(u32 size);
		static Ref<VertexBuffer> Create(f32* vertices, u32 size);
		
		void Bind() const;
		void Unbind() const;
		
		const BufferLayout& GetLayout() const;
		void SetLayout(const BufferLayout& layout);
		
	private:
		u32 m_RendererID;
		BufferLayout m_Layout;
	};

	class IndexBuffer
	{
	public:
		IndexBuffer(u32* indices, u32 count);
		virtual ~IndexBuffer();
		
		static Ref<IndexBuffer> Create(u32* indices, u32 count);
		
		void Bind() const;
		void Unbind() const;
		
		u32 GetCount() const;
		
	private:
		u32 m_RendererID;
		u32 m_Count;
	};
}
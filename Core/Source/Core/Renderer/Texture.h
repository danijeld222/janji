#pragma once

#include "Core/Defines.h"

#include <string>
#include <glad/gl.h>

namespace Core 
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		
		virtual void SetData(void* data, u32 size) = 0;
		
		virtual void Bind(u32 slot = 0) const = 0;
	};
	
	class Texture2D : public Texture
	{
	public:
		Texture2D(u32 width, u32 height);
		Texture2D(const std::string& path);
		virtual ~Texture2D();
		
		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		
		virtual void SetData(void* data, u32 size) override;
		
		virtual void Bind(u32 slot = 0) const override;
		
	private:
		std::string m_Path;
		u32 m_Width;
		u32 m_Height;
		u32 m_RendererID;
		GLenum m_InternalFormat;
		GLenum m_DataFormat;
	};
}
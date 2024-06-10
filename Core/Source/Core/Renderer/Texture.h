#pragma once

#include "Core/Defines.h"

#include <string>

namespace Core 
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		
		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;
		
		virtual void Bind(u32 slot = 0) const = 0;
	};
	
	class Texture2D : public Texture
	{
	public:
		Texture2D(const std::string& path);
		virtual ~Texture2D();
		
		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
		
		virtual void Bind(u32 slot = 0) const override;
		
	private:
		std::string m_Path;
		u32 m_Width;
		u32 m_Height;
		u32 m_RendererID;
	};
}
#include "Texture.h"
#include "Renderer.h"
#include "Core/Asserts.h"

#include "SDL_image.h"
#include <SDL3/SDL.h>
//#include <glad/gl.h>

namespace Core
{
	Texture2D::Texture2D(u32 width, u32 height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
	Texture2D::Texture2D(const std::string& path)
		: m_Path(path)
	{
		i32 width = 0;
		i32 height = 0;
		SDL_Surface* loadedSurface = IMG_Load(path.c_str());
		COREASSERT_MESSAGE(loadedSurface, "Failed to load image!");
		
		m_Width = loadedSurface->w;
		m_Height = loadedSurface->h;
		
		// NOTE: DANI - Currently we are using SDL_Image the issue is that when image (png) is loaded from disk we need to manualy
		//				flip it by. Take a look at stb_image library as there is stbi_set_flip_vertically_on_load(1); which 
		//				handles this automaticly when we load image from disk.
		
		SDL_LockSurface(loadedSurface);
		
		int pitch = loadedSurface->pitch;	// row size
		char* temp = new char[pitch];		// intermediate buffer
		char* pixels = (char*)loadedSurface->pixels;
		
		for (int i = 0; i < loadedSurface->h / 2; ++i) {
			// get pointers to the two rows to swap
			char* row1 = pixels + i * pitch;
			char* row2 = pixels + (loadedSurface->h - i - 1) * pitch;
			
			// swap rows
			memcpy(temp, row1, pitch);
			memcpy(row1, row2, pitch);
			memcpy(row2, temp, pitch);
		}
		
		delete[] temp;
		
		SDL_UnlockSurface(loadedSurface);
		
		SDL_Surface* formatedSurface = SDL_CreateSurface(loadedSurface->w, loadedSurface->h, SDL_PIXELFORMAT_ABGR8888);
		
		SDL_BlitSurface(loadedSurface, NULL, formatedSurface, NULL);
		
		m_InternalFormat = GL_RGB8;
		m_DataFormat = GL_RGBA;
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, formatedSurface->pixels);
		
		SDL_DestroySurface(formatedSurface);
		SDL_DestroySurface(loadedSurface);
	}
	
	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	
	void Texture2D::SetData(void* data, u32 size)
	{
		u32 bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		COREASSERT_MESSAGE(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}
	
	void Texture2D::Bind(u32 slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}
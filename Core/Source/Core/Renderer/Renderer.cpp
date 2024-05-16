#include "Renderer.h"
#include "Core/Asserts.h"
#include "Core/CoreMemory.h"

#include <vector>
#include <cmath>
#include <glad/gl.h>

#include "SDL3/SDL_surface.h"

#include "SDL_image.h"

namespace Core
{
    Renderer::Renderer(SDL_Window* window, u32 rendererFlags)
    {
        COREASSERT_MESSAGE(IMG_Init(IMG_INIT_PNG), "SDL Image faled to initialize");
        m_Context = SDL_GL_CreateContext(window);
        
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        printf("GL %d.%d\n", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
        
        SDL_GL_MakeCurrent(window, m_Context);
        SDL_GL_SetSwapInterval(1);
        
        // TODO: Dani - think about should this be moved to window class, because its showing window
        SDL_ShowWindow(window);
        
        m_Surface = SDL_GetWindowSurface(window);
        m_DebugSurface = nullptr;
        m_DebugTexture = nullptr;
        m_DebugSpriteSheetTexture = nullptr;
        
        COREASSERT_MESSAGE(m_Surface, SDL_GetError());
        
        m_BitmapMemory = static_cast<u8*>(CoreAllocate(m_Surface->w * m_Surface->h * 4, MEMORY_TAG_RENDERER));
        CoreZeroMemory(m_BitmapMemory, m_Surface->w * m_Surface->h * 4);
        
        // Debug 
        m_DebugPalette = SDL_CreatePalette(256);
        std::vector<SDL_Color> colors(256);
        for (int i = 0; i < 256; i++)
        {
            colors[i] = { (u8)(i * 1.0f), (u8)(i * 2.0f), (u8)(i * 5.0f), 0xFF };
        }
        SDL_SetPaletteColors(m_DebugPalette, colors.data(), 0, 256);
        
        m_DebugTextureRect = new SDL_FRect();
        m_DebugTextureRect->x = 0;
        m_DebugTextureRect->y = 0;
        m_DebugTextureRect->w = 1280;
        m_DebugTextureRect->h = 720;
        
        //std::string texturePath = "DebugGraphics/Spritesheet/DebugSpritesheet.png";
        //SDL_Surface* loadedSurface = IMG_Load(texturePath.c_str());
        //if (loadedSurface == NULL)
        //{
        //    printf("Unable to load image %s! SDL_image Error: %s\n", texturePath.c_str(), IMG_GetError());
        //}
        //else
        //{
        //    //Color key image
        //    SDL_SetSurfaceColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        //    
        //    //Create texture from surface pixels
        //    m_DebugSpriteSheetTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
        //    if (m_DebugSpriteSheetTexture == NULL)
        //    {
        //        printf("Unable to create texture from %s! SDL Error: %s\n", texturePath.c_str(), SDL_GetError());
        //    }
        //    
        //    //Get rid of old loaded surface
        //    SDL_DestroySurface(loadedSurface);
        //}
    }

    Renderer::~Renderer()
    {
        // This is probably not necessary
        CoreFree(m_BitmapMemory, m_Surface->w * m_Surface->h * 4, MEMORY_TAG_RENDERER);
        
        SDL_DestroySurface(m_Surface);
        SDL_DestroySurface(m_DebugSurface);
        
        SDL_GL_DeleteContext(m_Context);
        
        IMG_Quit();
    }
    
    void Renderer::SwapBuffers()
    {
        SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
    }
    
    void Renderer::ClearScreen()
    {
        u8 redChannel = 0;
        u8 greenChannel = 85;
        u8 blueChannel = 170;
        u8 alphaChannel = 255;
        
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(redChannel, greenChannel, blueChannel, alphaChannel);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void Renderer::ClearScreen(u8 red, u8 green, u8 blue, u8 alpha)
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(red, green, blue, alpha);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void Renderer::Update(SDL_Window* window)
    {
        RenderDebugGradient(m_DebugXOffset, m_DebugYOffset);
        
        m_DebugXOffset++;
        m_DebugYOffset++;
        
        SDL_DestroySurface(m_DebugSurface);
        
        //SDL_RenderTexture(m_Renderer, m_DebugTexture, NULL, m_DebugTextureRect);
        SDL_DestroyTexture(m_DebugTexture);
        
        if (m_DebugSpriteSheetTexture)
        {
            f32 FrameRateMultiplier = 0.15f;
            if (std::floorf(m_DebugSpriteSheetCurrentFrame * FrameRateMultiplier) >= m_DebugSpriteSheetFrameNumber)
            {
                m_DebugSpriteSheetCurrentFrame = 0;
            }
            
            f32 CurrentSpriteSheetFrame = std::floorf(m_DebugSpriteSheetCurrentFrame * FrameRateMultiplier);
            
            SDL_FRect renderQuad = { 200, 200, 300, 200 };
            SDL_FRect spriteClip = { CurrentSpriteSheetFrame * 300, 0, 300, 200 };
            
            //SDL_RenderTexture(m_Renderer, m_DebugSpriteSheetTexture, &spriteClip, &renderQuad);
            
            m_DebugSpriteSheetCurrentFrame++;
        }
    }

    void Renderer::SetPixel(SDL_Surface* surface, i32 x, i32 y, u32 pixel)
    {
        u32* const target_pixel = (u32*)((u8*)surface->pixels
            + y * surface->pitch
            + x * surface->format->bytes_per_pixel);
        *target_pixel = pixel;
    }

    void Renderer::RenderDebugGradient(i32 xOffset, i32 yOffset)
    {
        i32 pitch = m_Surface->w * m_Surface->format->bytes_per_pixel;
        
        u8* row = (u8*)m_BitmapMemory;
        for (i32 y = 0; y < m_Surface->h; y++)
        {
            u8* pixel = (u8*)row;
            for (i32 x = 0; x < m_Surface->w; x++)
            {
                *pixel = (u8)(x + xOffset);
                ++pixel;
                
                *pixel = (u8)(y + yOffset);
                ++pixel;
                
                *pixel = 0;
                ++pixel;
                
                *pixel = 0;
                ++pixel;
            }
            
            row += pitch;
        }
        
        m_DebugSurface = SDL_CreateSurfaceFrom(m_BitmapMemory, m_Surface->w, m_Surface->h, m_Surface->w * 4, SDL_PIXELFORMAT_INDEX8);
        SDL_SetSurfacePalette(m_DebugSurface, m_DebugPalette);
        //m_DebugTexture = SDL_CreateTextureFromSurface(m_Renderer, m_DebugSurface);
        
        COREASSERT_MESSAGE(m_DebugSurface, SDL_GetError());
        //COREASSERT_MESSAGE(m_DebugTexture, SDL_GetError());
    }
    
    SDL_GLContext Renderer::GetOpenGLContext()
    {
        return m_Context;
    }
}
#include "Renderer.h"
#include "Core/Asserts.h"
#include "Core/CoreMemory.h"
#include "Core/Logger/Logger.h"

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
        COREINFO("GL {0}.{1}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
        
        COREINFO("OpenGL Info:");
        COREINFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
        COREINFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
        COREINFO("  Version: {0}", (char*)glGetString(GL_VERSION));
        
        SDL_GL_MakeCurrent(window, m_Context);
        SDL_GL_SetSwapInterval(1);
        
        // TODO: Dani - think about should this be moved to window class, because its showing window
        SDL_ShowWindow(window);
        
        m_WindowSurface = SDL_GetWindowSurface(window);
        COREASSERT_MESSAGE(m_WindowSurface, SDL_GetError());
    }

    Renderer::~Renderer()
    {
        SDL_DestroySurface(m_WindowSurface);
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
        
    }
    
    SDL_GLContext Renderer::GetOpenGLContext()
    {
        return m_Context;
    }
}
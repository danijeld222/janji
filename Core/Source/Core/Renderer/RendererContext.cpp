#include "RendererContext.h"

#include "Core/Asserts.h"
#include "Core/Logger/Logger.h"

#include <vector>
#include <cmath>
#include <glad/gl.h>

#include "SDL3/SDL_surface.h"

#include "SDL_image.h"

namespace Core 
{
    RendererContext::RendererContext(SDL_Window* window, u32 rendererFlags)
        : m_Window(window)
    {
        COREASSERT_MESSAGE(window, "Window is nullptr!");
        
        COREASSERT_MESSAGE(IMG_Init(IMG_INIT_PNG), "SDL Image faled to initialize");
        m_Context = SDL_GL_CreateContext(m_Window);
        
        int version = gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
        COREINFO("GL {0}.{1}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
        
        COREINFO("OpenGL Info:");
        COREINFO("  Vendor: {0}", (char*)glGetString(GL_VENDOR));
        COREINFO("  Renderer: {0}", (char*)glGetString(GL_RENDERER));
        COREINFO("  Version: {0}", (char*)glGetString(GL_VERSION));
        
        SDL_GL_MakeCurrent(m_Window, m_Context);
        SDL_GL_SetSwapInterval(1);
        
        // TODO: Dani - think about should this be moved to window class, because its showing window
        SDL_ShowWindow(m_Window);
        
        m_WindowSurface = SDL_GetWindowSurface(m_Window);
        COREASSERT_MESSAGE(m_WindowSurface, SDL_GetError());
    }
    
    RendererContext::~RendererContext()
    {
        SDL_DestroySurface(m_WindowSurface);
        SDL_GL_DeleteContext(m_Context);
        
        IMG_Quit();
    }
    
    void RendererContext::SwapBuffers()
    {
        SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
    }
    
    SDL_GLContext RendererContext::GetOpenGLContext()
    {
        return m_Context;
    }
}
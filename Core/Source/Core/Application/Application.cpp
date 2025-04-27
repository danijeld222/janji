#include "Application.h"
#include "Core/Asserts.h"
#include "Core/Logger/Logger.h"
#include "Core/CoreMemory.h"

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RendererCommands.h"

#include "Core/Debug/Instrumentor.h"

#include <functional>

namespace Core 
{
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        CORE_PROFILE_FUNCTION();
        
        COREASSERT_MESSAGE(!s_Instance, "We already have instance, Application should be singleton");
        s_Instance = this;
        
        InitializeMemoryStats();
        Core::Logger::Initialize();
        
        m_Window = Scope<WindowBase>(WindowBase::Create());
        m_Window->SetEventCallback(CORE_BIND_EVENT_FN(Application::OnEvent));
        
        Renderer::Init();
        
        m_Running = true;
        
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }
    
    Application::~Application()
    {
        CORE_PROFILE_FUNCTION();
        
        Renderer::Shutdown();
        
        ShutdownMemoryStats();
        Core::Logger::Shutdown();
    }
    
    void Application::PushLayer(Layer* layer)
    {
        CORE_PROFILE_FUNCTION();
        
        m_LayerStack.PushLayer(layer);
    }
    
    void Application::PushOverlay(Layer* layer)
    {
        CORE_PROFILE_FUNCTION();
        
        m_LayerStack.PushOverlay(layer);
    }
    
    void Application::OnEvent(Event& e)
    {
        CORE_PROFILE_FUNCTION();
        
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(CORE_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(CORE_BIND_EVENT_FN(Application::OnWindowResize));
        dispatcher.Dispatch<WindowMinimizedEvent>(CORE_BIND_EVENT_FN(Application::OnWindowMinimized));
        
        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }
    
    void Application::ApplicationRun()
    {
        //COREINFO(GetMemoryUsage());
        
        CORE_PROFILE_FUNCTION();
        
        while (m_Running)
        {
            CORE_PROFILE_SCOPE("RunLoop");
            
            f32 time = (f32)SDL_GetTicks(); // NOTE: Dani - This will wrap if program runs more then 49 days https://wiki.libsdl.org/SDL2/SDL_GetTicks
            time *= 0.001f;                 // NOTE: Dani - Convert to seconds
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            
            if (!m_Minimized)
            {
                {
                    CORE_PROFILE_SCOPE("LayerStack OnUpdate");
                    
                    for (Layer* layer : m_LayerStack)
                    {
                        layer->OnUpdate(timestep);
                    }
                }
                
                m_ImGuiLayer->Begin();
                {
                    CORE_PROFILE_SCOPE("LayerStack OnImGuiRender");
                    
                    for (Layer* layer : m_LayerStack)
                    {
                        layer->OnImGuiRender();
                    }
                }
                m_ImGuiLayer->End();
            }
            
            // NOTE: Dani - We should probably not swap buffer if window is minimized
            m_Window->OnUpdate();
        }
    }
    
    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        
        return true;
    }
    
    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        CORE_PROFILE_FUNCTION();
        
        if (e.GetWidth() == 0 || e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
        
        return false;
    }
    
    bool Application::OnWindowMinimized(WindowMinimizedEvent& e)
    {
        CORE_PROFILE_FUNCTION();
        
        m_Minimized = e.GetIsMinimized();
        
        return false;
    }
}
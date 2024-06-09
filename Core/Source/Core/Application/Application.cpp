#include "Application.h"
#include "Core/Asserts.h"
#include "Core/Logger/Logger.h"
#include "Core/CoreMemory.h"

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/RendererCommands.h"

#include <functional>

namespace Core 
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        COREASSERT_MESSAGE(!s_Instance, "We already have instance, Application should be singleton");
        s_Instance = this;
        
        InitializeMemoryStats();
        Core::Logger::Initialize();
        
        m_Window = Scope<WindowBase>(WindowBase::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        
        m_Running = true;
        
        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }
    
    Application::~Application()
    {
        ShutdownMemoryStats();
        Core::Logger::Shutdown();
    }
    
    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    
    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
    
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
            {
                break;
            }
        }
    }
    
    void Application::ApplicationRun()
    {
        //COREINFO(GetMemoryUsage());
        
        while (m_Running)
        {
            f32 time = (f32)SDL_GetTicks(); // NOTE: Dani - This will wrap if program runs more then 49 days https://wiki.libsdl.org/SDL2/SDL_GetTicks
            time *= 0.001f;                 // NOTE: Dani - Convert to seconds
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }
            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            
            m_Window->OnUpdate();
        }
    }
    
    b8 Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
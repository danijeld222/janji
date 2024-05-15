#include "Application.h"
#include "Core/Asserts.h"
#include "Core/Logger/Logger.h"
#include "Core/CoreMemory.h"

#include <functional>

namespace Core {
    
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
    
    Application* Application::s_Instance = nullptr;
    
    Application::Application()
    {
        COREASSERT_MESSAGE(!s_Instance, "We already have instance, Application should be singleton");
        s_Instance = this;
        
        InitializeMemoryStats();
        Core::Logger::Initialize();
        
        m_Window = std::unique_ptr<WindowBase>(WindowBase::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        
        m_Window->InitRenderer();

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
        COREINFO(GetMemoryUsage());
        
        while (m_Running)
        {
            m_Window->RendererBegin();
            
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
            m_Window->RendererUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            
            m_Window->OnUpdate();
            
            m_Window->RendererSwapBuffers();
        }
    }
    
    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
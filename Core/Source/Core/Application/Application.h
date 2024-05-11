#pragma once

#include "Core/Defines.h"
#include "Core/GameType.h"
#include "Core/Window/WindowBase.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Layer/LayerStack.h"
#include "Core/ImGui/ImGuiLayer.h"

namespace Core 
{
    class Application
    {
    public:
        Application();
        virtual ~Application();  // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
        
        void ApplicationRun();
        void OnEvent(Event& e);
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        inline WindowBase& GetWindow() { return *m_Window; }
        
        inline static Application& Get() { return *s_Instance; }
        
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        
        b8 m_Running = false;
        std::unique_ptr<WindowBase> m_Window;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        
        static Application* s_Instance;
    };
    
    Application* CreateApplication();
}
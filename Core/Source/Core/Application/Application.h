#pragma once

#include "Core/Defines.h"
#include "Core/Window/WindowBase.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Layer/LayerStack.h"
#include "Core/ImGui/ImGuiLayer.h"
#include "Core/Time/Timestep.h"

int main(int argc, char** argv);

namespace Core 
{
    class Application
    {
    public:
        Application();
        virtual ~Application();  // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
        
        void OnEvent(Event& e);
        
        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
        
        WindowBase& GetWindow() { return *m_Window; }
        
        static Application& Get() { return *s_Instance; }
        
    private:
        void ApplicationRun();
        
        b8 OnWindowClose(WindowCloseEvent& e);
        b8 OnWindowResize(WindowResizeEvent& e);
        b8 OnWindowMinimized(WindowMinimizedEvent& e);
        
        b8 m_Running = false;
        b8 m_Minimized = false;
        Scope<WindowBase> m_Window;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        
        f32 m_LastFrameTime = 0.0f;
        
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
    };
    
    Application* CreateApplication();
}
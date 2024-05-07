#pragma once

#include "Core/Defines.h"
#include "Core/GameType.h"
#include "Core/Window/WindowBase.h"

namespace Core 
{
    struct ApplicationState
    {
        Game* gameInstance;
        b8 isRunning;
        b8 isSuspended;
        i16 width;
        i16 height;
        f64 lastTime;
    };
    
    class COREAPI Application
    {
    public:
        Application();
        virtual ~Application();  // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
        
        void ApplicationRun();
        //void OnEvent(Event& e);
        
    private:
        //bool OnWindowClose(WindowCloseEvent& e);
        
        b8 m_Running = false;
        ApplicationState m_AppState;
        WindowBase* m_Window;
        
        //std::unique_ptr<WindowBase> m_Window;
    };
    
    Application* CreateApplication();
}
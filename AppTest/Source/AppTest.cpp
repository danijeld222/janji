#include <Core.h>
#include <Core/EntryPoint.h>

#include "TestingLayer.h"
#include "AppTest2D.h"

class Sandbox : public Core::Application
{
public:
    Sandbox()
    {
        //PushLayer(new TestingLayer());
        PushLayer(new AppTest2D());
    }
    
    ~Sandbox()
    {
    }
};

Core::Application* Core::CreateApplication()
{
    return new Sandbox();
}
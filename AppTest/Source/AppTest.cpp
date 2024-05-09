#include <Core.h>

class TestingLayer : public Core::Layer
{
public:
    TestingLayer() : Layer("Testing")
    {
        // Constructor
    }
    
    void OnUpdate() override
    {
        //COREINFO("TestingLayer UPDATE");
    }
    
    void OnEvent(Core::Event& event) override
    {
        //COREINFO(event.ToString().c_str());
    }
};

class Sandbox : public Core::Application
{
public:
    Sandbox()
    {
        PushLayer(new TestingLayer());
    }

    ~Sandbox()
    {

    }

};

Core::Application* Core::CreateApplication()
{
    return new Sandbox();
}
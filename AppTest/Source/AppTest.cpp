#include <Core/Application/Application.h>
#include <Core/EntryPoint.h>

class Sandbox : public Core::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }

};

Core::Application* Core::CreateApplication()
{
    return new Sandbox();
}
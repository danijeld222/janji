#include <Core.h>

#include "imgui.h"

class TestingLayer : public Core::Layer
{
public:
    TestingLayer() : Layer("Testing")
    {
        // Constructor
    }
    
    void OnUpdate() override
    {
        //if (Core::InputBase::IsKeyPressed(SDL_SCANCODE_TAB))
        //{
        //    CORETRACE("SDL_SCANCODE_TAB");
        //}
        //
        //if (Core::InputBase::IsMouseButtonPressed(SDL_BUTTON_LEFT))
        //{
        //    CORETRACE("SDL_BUTTON_LEFT");
        //}

        //CORETRACE("SDL MOUSE X {0}", Core::InputBase::GetMouseX());
        //CORETRACE("SDL MOUSE Y {0}", Core::InputBase::GetMouseY());
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Testing Test");
        ImGui::End();
    }
    
    void OnEvent(Core::Event& event) override
    {
        //if (event.ShouldLog())
        //{
            //CORETRACE("TestingLayer {0}", event.ToString());
        //}
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
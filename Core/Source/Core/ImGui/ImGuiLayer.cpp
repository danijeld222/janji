#include "ImGuiLayer.h"

#include "Core/Application/Application.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Defines.h"
#include "Core/Logger/Logger.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_sdlrenderer3.h"
#include <stdio.h>
#include <sstream>

namespace Core
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
		
	}

	ImGuiLayer::~ImGuiLayer()
	{
		
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		
		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		SDL_Window* SDLWindow = static_cast<SDL_Window*>(app.GetWindow().GetNativeWindow());
		Renderer* _Renderer = static_cast<Renderer*>(app.GetWindow().GetRenderer());

		ImGui_ImplSDL3_InitForSDLRenderer(SDLWindow, _Renderer->GetSDLRenderer());
		ImGui_ImplSDLRenderer3_Init(_Renderer->GetSDLRenderer());
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		// Rendering
		ImGui::Render();

		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnImGuiRender()
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 3.0f, 3.0f), 0, ImVec2(1.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
		ImGui::Begin("Testing", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
		ImGui::PopStyleVar(2);
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<GenericSDL_Event>(CORE_BIND_EVENT_FN(ImGuiLayer::OnGenericSDLEvent));
	}

	bool ImGuiLayer::OnGenericSDLEvent(GenericSDL_Event& e)
	{
		ImGui_ImplSDL3_ProcessEvent(e.GetSDLEvent());
		
		return true;
	}
}
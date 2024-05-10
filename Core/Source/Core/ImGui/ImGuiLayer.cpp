#include "ImGuiLayer.h"

#include "Core/Application/Application.h"
#include "Core/Window/Window.h"
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
		
		m_Renderer = SDL_CreateRenderer(SDLWindow, nullptr, SDL_RENDERER_PRESENTVSYNC);
		
		ImGui_ImplSDL3_InitForSDLRenderer(SDLWindow, m_Renderer);
		ImGui_ImplSDLRenderer3_Init(m_Renderer);
	}

	void ImGuiLayer::OnDetach()
	{
		// This is how imgui SDL3 example is shuting down
		ImGui_ImplSDLRenderer3_Shutdown();
		SDL_DestroyRenderer(m_Renderer);
		
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		u8 redChannel = 0;
		u8 greenChannel = 85;
		u8 blueChannel = 170;
		u8 alphaChannel = 255;
		
		SDL_SetRenderDrawColor(m_Renderer, redChannel, greenChannel, blueChannel, alphaChannel);
		SDL_RenderClear(m_Renderer);
		
		ImGuiIO& io = ImGui::GetIO();
		
		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - 3.0f, 3.0f), 0, ImVec2(1.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
		ImGui::Begin("Testing", nullptr, ImGuiWindowFlags_NoDecoration);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();
		ImGui::PopStyleVar(2);
		
		// Rendering
		ImGui::Render();
		
		// Update and Render additional Platform Windows
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		
		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
		
		SDL_RenderPresent(m_Renderer);
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<GenericSDL_Event>(BIND_EVENT_FN(ImGuiLayer::OnGenericSDLEvent));
	}

	bool ImGuiLayer::OnGenericSDLEvent(GenericSDL_Event& e)
	{
		ImGui_ImplSDL3_ProcessEvent(e.GetSDLEvent());
		
		return true;
	}
}
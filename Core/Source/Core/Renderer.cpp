#include "Renderer.h"
#include "Asserts.h"

#include "imgui.h"
#include "imgui_impl_sdlrenderer3.h"

Renderer::Renderer(SDL_Window* Window, u32 RendererFlags)
{
    pRenderer = SDL_CreateRenderer(Window, nullptr, RendererFlags);
    COREASSERT_MESSAGE(pRenderer, SDL_GetError());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    ImGui_ImplSDL3_InitForSDLRenderer(Window, pRenderer);
    ImGui_ImplSDLRenderer3_Init(pRenderer);
}

Renderer::~Renderer()
{
    ImGui_ImplSDLRenderer3_Shutdown();
    SDL_DestroyRenderer(pRenderer);
}

void Renderer::ClearScreen(i32 r, i32 g, i32 b, i32 a)
{
    SDL_SetRenderDrawColor(pRenderer, r, g, b, a);
    SDL_RenderClear(pRenderer);
}

void Renderer::Update()
{
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(pRenderer);
}

void Renderer::Render()
{
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
}

SDL_Renderer* Renderer::GetRenderer()
{
    return pRenderer;
}
#include "Renderer.h"
#include "Asserts.h"
#include <vector>
#include "SDL3/SDL_surface.h"

Renderer::Renderer(SDL_Window* Window, u32 RendererFlags)
{
    pRenderer = SDL_CreateRenderer(Window, nullptr, RendererFlags);
    pSurface = SDL_GetWindowSurface(Window);

    COREASSERT_MESSAGE(pRenderer, SDL_GetError());
    COREASSERT_MESSAGE(pSurface, SDL_GetError());

    BitmapMemory = static_cast<u8*>(malloc(pSurface->w * pSurface->h * 4));
    memset(BitmapMemory, 0, pSurface->w * pSurface->h * 4);

    // Debug 
    DebugPalette = SDL_CreatePalette(256);
    std::vector<SDL_Color> Colors(256);
    for (int i = 0; i < 256; i++)
    {
        Colors[i] = { (u8)i, (u8)i, (u8)i, 0xFF };
    }
    SDL_SetPaletteColors(DebugPalette, Colors.data(), 0, 256);

    DebugTextureRect = new SDL_FRect();
    DebugTextureRect->x = 0;
    DebugTextureRect->y = 0;
    DebugTextureRect->w = 1280;
    DebugTextureRect->h = 720;

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
    // This is probably not necessary
    SDL_DestroySurface(pSurface);
    SDL_DestroySurface(pDebugSurface);
    free(BitmapMemory);
    
    // This is how imgui SDL3 example is shuting down
    ImGui_ImplSDLRenderer3_Shutdown();
    SDL_DestroyRenderer(pRenderer);
}

void Renderer::ClearScreen(u8 Red, u8 Green, u8 Blue, u8 Alpha)
{
    SDL_SetRenderDrawColor(pRenderer, Red, Green, Blue, Alpha);
    SDL_RenderClear(pRenderer);
}

void Renderer::Update(SDL_Window* Window)
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

    RenderDebugGradient(DebugXOffset, DebugYOffset);
    
    DebugXOffset++;
    DebugYOffset++;
    
    SDL_DestroySurface(pDebugSurface);
}

void Renderer::SetPixel(SDL_Surface* Surface, int x, int y, u32 Pixel)
{
    u32* const target_pixel = (u32*)((u8*)Surface->pixels
        + y * Surface->pitch
        + x * Surface->format->bytes_per_pixel);
    *target_pixel = Pixel;
}

void Renderer::RenderDebugGradient(i32 XOffset, i32 YOffset)
{
    i32 Pitch = pSurface->w * pSurface->format->bytes_per_pixel;
    
    u8* Row = (u8*)BitmapMemory;
    for (i32 y = 0; y < pSurface->h; y++)
    {
        u8* Pixel = (u8*)Row;
        for (i32 x = 0; x < pSurface->w; x++)
        {
            *Pixel = (u8)(x + XOffset);
            ++Pixel;
            
            *Pixel = (u8)(y + YOffset);
            ++Pixel;
            
            *Pixel = 0;
            ++Pixel;
            
            *Pixel = 0;
            ++Pixel;
        }
        
        Row += Pitch;
    }

    pDebugSurface = SDL_CreateSurfaceFrom(BitmapMemory, pSurface->w, pSurface->h, pSurface->w * 4, SDL_PIXELFORMAT_INDEX8);
    SDL_SetSurfacePalette(pDebugSurface, DebugPalette);
    pDebugTexture = SDL_CreateTextureFromSurface(pRenderer, pDebugSurface);
    
    COREASSERT_MESSAGE(pDebugSurface, SDL_GetError());
    COREASSERT_MESSAGE(pDebugTexture, SDL_GetError());
}

void Renderer::Render()
{
    SDL_RenderTexture(pRenderer, pDebugTexture, NULL, DebugTextureRect);

    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
    
    SDL_RenderPresent(pRenderer);

    SDL_DestroyTexture(pDebugTexture);
}

SDL_Renderer* Renderer::GetRenderer()
{
    return pRenderer;
}
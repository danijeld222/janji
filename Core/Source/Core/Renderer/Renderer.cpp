#include "Renderer.h"
#include "Core/Asserts.h"
#include "Core/CoreMemory.h"

#include <vector>
#include "SDL3/SDL_surface.h"

namespace Core
{
    Renderer::Renderer(SDL_Window* window, u32 rendererFlags)
    {
        m_Renderer = SDL_CreateRenderer(window, nullptr, rendererFlags);
        m_Surface = SDL_GetWindowSurface(window);
        m_DebugSurface = nullptr;
        m_DebugTexture = nullptr;

        COREASSERT_MESSAGE(m_Renderer, SDL_GetError());
        COREASSERT_MESSAGE(m_Surface, SDL_GetError());

        m_BitmapMemory = static_cast<u8*>(CoreAllocate(m_Surface->w * m_Surface->h * 4, MEMORY_TAG_RENDERER));
        CoreZeroMemory(m_BitmapMemory, m_Surface->w * m_Surface->h * 4);

        // Debug 
        m_DebugPalette = SDL_CreatePalette(256);
        std::vector<SDL_Color> colors(256);
        for (int i = 0; i < 256; i++)
        {
            colors[i] = { (u8)(i * 1.0f), (u8)(i * 2.0f), (u8)(i * 5.0f), 0xFF };
        }
        SDL_SetPaletteColors(m_DebugPalette, colors.data(), 0, 256);

        m_DebugTextureRect = new SDL_FRect();
        m_DebugTextureRect->x = 0;
        m_DebugTextureRect->y = 0;
        m_DebugTextureRect->w = 1280;
        m_DebugTextureRect->h = 720;

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

        ImGui_ImplSDL3_InitForSDLRenderer(window, m_Renderer);
        ImGui_ImplSDLRenderer3_Init(m_Renderer);
    }

    Renderer::~Renderer()
    {
        // This is probably not necessary
        CoreFree(m_BitmapMemory, m_Surface->w * m_Surface->h * 4, MEMORY_TAG_RENDERER);

        SDL_DestroySurface(m_Surface);
        SDL_DestroySurface(m_DebugSurface);

        // This is how imgui SDL3 example is shuting down
        ImGui_ImplSDLRenderer3_Shutdown();
        SDL_DestroyRenderer(m_Renderer);

        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void Renderer::ClearScreen(u8 red, u8 green, u8 blue, u8 alpha)
    {
        SDL_SetRenderDrawColor(m_Renderer, red, green, blue, alpha);
        SDL_RenderClear(m_Renderer);
    }

    void Renderer::Update(SDL_Window* window)
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

        RenderDebugGradient(m_DebugXOffset, m_DebugYOffset);

        m_DebugXOffset++;
        m_DebugYOffset++;

        SDL_DestroySurface(m_DebugSurface);
    }

    void Renderer::SetPixel(SDL_Surface* surface, int x, int y, u32 pixel)
    {
        u32* const target_pixel = (u32*)((u8*)surface->pixels
            + y * surface->pitch
            + x * surface->format->bytes_per_pixel);
        *target_pixel = pixel;
    }

    void Renderer::RenderDebugGradient(i32 xOffset, i32 yOffset)
    {
        i32 pitch = m_Surface->w * m_Surface->format->bytes_per_pixel;

        u8* row = (u8*)m_BitmapMemory;
        for (i32 y = 0; y < m_Surface->h; y++)
        {
            u8* pixel = (u8*)row;
            for (i32 x = 0; x < m_Surface->w; x++)
            {
                *pixel = (u8)(x + xOffset);
                ++pixel;

                *pixel = (u8)(y + yOffset);
                ++pixel;

                *pixel = 0;
                ++pixel;

                *pixel = 0;
                ++pixel;
            }

            row += pitch;
        }

        m_DebugSurface = SDL_CreateSurfaceFrom(m_BitmapMemory, m_Surface->w, m_Surface->h, m_Surface->w * 4, SDL_PIXELFORMAT_INDEX8);
        SDL_SetSurfacePalette(m_DebugSurface, m_DebugPalette);
        m_DebugTexture = SDL_CreateTextureFromSurface(m_Renderer, m_DebugSurface);

        COREASSERT_MESSAGE(m_DebugSurface, SDL_GetError());
        COREASSERT_MESSAGE(m_DebugTexture, SDL_GetError());
    }

    void Renderer::Render()
    {
        SDL_RenderTexture(m_Renderer, m_DebugTexture, NULL, m_DebugTextureRect);

        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());

        SDL_RenderPresent(m_Renderer);

        SDL_DestroyTexture(m_DebugTexture);
    }

    void Renderer::Run(SDL_Window* window)
    {
        u8 redChannel = 0;
        u8 greenChannel = 85;
        u8 blueChannel = 170;
        u8 alphaChannel = 255;

        //while (m_Events->HandleEvents(m_Window->GetWindow()))
        //{
            ClearScreen(redChannel, greenChannel, blueChannel, alphaChannel);
            Update(window);
            Render();

            //redChannel++;
            //greenChannel++;
            //blueChannel++;
        //}
    }

    SDL_Renderer* Renderer::GetRenderer()
    {
        return m_Renderer;
    }
}
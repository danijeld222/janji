#pragma once

#include "Core/Defines.h"

#include "Core/Layer/Layer.h"
#include "Core/Events/Event.h"
//#include <SDL3/SDL.h>
//#include "Core/Renderer/Renderer.h"

//#include "imgui.h"
//#include "imgui_impl_sdl3.h"
//#include "imgui_impl_sdlrenderer3.h"
//#include <stdio.h>
#include <SDL3/SDL.h>

namespace Core
{
	class COREAPI ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnGenericSDLEvent(GenericSDL_Event& e);

		SDL_Renderer* m_Renderer;

	};

}
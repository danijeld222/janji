#pragma once

#include "Core/Defines.h"

#include "Core/Layer/Layer.h"
#include "Core/Events/Event.h"
#include <SDL3/SDL.h>

namespace Core
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;
		
		void Begin();
		void End();
		
	private:
		bool OnGenericSDLEvent(GenericSDL_Event& e);
		
		SDL_Renderer* m_Renderer;
	};
}
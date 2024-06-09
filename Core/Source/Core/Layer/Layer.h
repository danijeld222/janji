#pragma once

#include "Core/Defines.h"
#include "Core/Events/Event.h"
#include "Core/Time/Timestep.h"

namespace Core
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}
		
		inline const std::string& GetName() const { return m_DebugName; }
		
	protected:
		std::string m_DebugName;
	};
}
#pragma once

#include "Core/Defines.h"

#include <utility>

namespace Core
{
	class InputBase
	{
	protected:
		InputBase() = default;
		
	public:
		InputBase(const InputBase&) = delete;
		InputBase& operator=(const InputBase&) = delete;
		
		static bool IsKeyPressed(i32 keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
		
		static bool IsMouseButtonPressed(i32 button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		static std::pair<f32, f32> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static f32 GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static f32 GetMouseY() { return s_Instance->GetMouseYImpl(); }
		
	protected:
		virtual bool IsKeyPressedImpl(i32 keycode) = 0;
		
		virtual bool IsMouseButtonPressedImpl(i32 button) = 0;
		virtual std::pair<f32, f32> GetMousePositionImpl() = 0;
		virtual f32 GetMouseXImpl() = 0;
		virtual f32 GetMouseYImpl() = 0;
		
	private:
		static InputBase* s_Instance;
	};
}
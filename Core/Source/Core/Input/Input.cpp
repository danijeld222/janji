#include "Input.h"

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>

namespace Core
{
	InputBase* InputBase::s_Instance = new Input();

	bool Input::IsKeyPressedImpl(i32 keycode)
	{
		const u8* state = SDL_GetKeyboardState(NULL);
		bool keystate = state[keycode];
		return keystate;
	}

	bool Input::IsMouseButtonPressedImpl(i32 button)
	{
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	std::pair<f32, f32> Input::GetMousePositionImpl()
	{
		f32 xPos, yPos;
		SDL_GetMouseState(&xPos, &yPos);

		return { xPos, yPos };
	}

	f32 Input::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	f32 Input::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
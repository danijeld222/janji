#include "Input.h"

#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>

namespace Core
{
	InputBase* InputBase::s_Instance = new Input();

	bool Input::IsKeyPressedImpl(int keycode)
	{
		const u8* state = SDL_GetKeyboardState(NULL);
		b8 keystate = state[keycode];
		return keystate;
	}

	bool Input::IsMouseButtonPressedImpl(int button)
	{
		return SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(button);
	}

	std::pair<float, float> Input::GetMousePositionImpl()
	{
		float xPos, yPos;
		SDL_GetMouseState(&xPos, &yPos);

		return { xPos, yPos };
	}

	float Input::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float Input::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}
#pragma once

#include "Core/Input/InputBase.h"

namespace Core 
{
	class Input : public InputBase
	{
	protected:
		virtual bool IsKeyPressedImpl(i32 keycode) override;

		virtual bool IsMouseButtonPressedImpl(i32 button) override;
		virtual std::pair<f32, f32> GetMousePositionImpl() override;
		virtual f32 GetMouseXImpl() override;
		virtual f32 GetMouseYImpl() override;
	};
}
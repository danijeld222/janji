#pragma once

#include "Core/Defines.h"
#include <SDL3/SDL_events.h>
#include <functional>
#include <string>
#include <iostream>
#include <sstream>

namespace Core
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowMinimized, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		Test
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
		EventCategoryTest = BIT(5)
	};

	class Event
	{
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual i32 GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		virtual bool ShouldLog() const { return true; }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class GenericSDL_Event : public Event
	{
	public:
		GenericSDL_Event(SDL_Event* _event)
			: event(_event) {
		}

		SDL_Event* GetSDLEvent() const { return event; }

		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "GenericSDL_Event: " << GetEventTypeName();
			return stringOutput.str();
		}

		static EventType GetStaticType() { return EventType::Test; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "Test"; }
		virtual bool ShouldLog() const override
		{
			return (event->type != SDL_EVENT_POLL_SENTINEL);
		}

		virtual i32 GetCategoryFlags() const override { return EventCategoryTest; }

		std::string GetEventTypeName() const
		{
			switch (event->type)
			{
			case SDL_EVENT_FIRST:
				return "SDL_EVENT_FIRST";
			case SDL_EVENT_QUIT:
				return "SDL_EVENT_QUIT";
			case SDL_EVENT_TERMINATING:
				return "SDL_EVENT_TERMINATING";
			case SDL_EVENT_LOW_MEMORY:
				return "SDL_EVENT_LOW_MEMORY";
			case SDL_EVENT_WILL_ENTER_BACKGROUND:
				return "SDL_EVENT_WILL_ENTER_BACKGROUND";
			case SDL_EVENT_DID_ENTER_BACKGROUND:
				return "SDL_EVENT_DID_ENTER_BACKGROUND";
			case SDL_EVENT_WILL_ENTER_FOREGROUND:
				return "SDL_EVENT_WILL_ENTER_FOREGROUND";
			case SDL_EVENT_DID_ENTER_FOREGROUND:
				return "SDL_EVENT_DID_ENTER_FOREGROUND";
			case SDL_EVENT_LOCALE_CHANGED:
				return "SDL_EVENT_LOCALE_CHANGED";
			case SDL_EVENT_SYSTEM_THEME_CHANGED:
				return "SDL_EVENT_SYSTEM_THEME_CHANGED";
			case SDL_EVENT_DISPLAY_ORIENTATION:
				return "SDL_EVENT_DISPLAY_ORIENTATION";
			case SDL_EVENT_DISPLAY_ADDED:
				return "SDL_EVENT_DISPLAY_ADDED";
			case SDL_EVENT_DISPLAY_REMOVED:
				return "SDL_EVENT_DISPLAY_REMOVED";
			case SDL_EVENT_DISPLAY_MOVED:
				return "SDL_EVENT_DISPLAY_MOVED";
			case SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED:
				return "SDL_EVENT_DISPLAY_CONTENT_SCALE_CHANGED";
			case SDL_EVENT_DISPLAY_HDR_STATE_CHANGED:
				return "SDL_EVENT_DISPLAY_HDR_STATE_CHANGED";
			case SDL_EVENT_WINDOW_SHOWN:
				return "SDL_EVENT_WINDOW_SHOWN";
			case SDL_EVENT_WINDOW_HIDDEN:
				return "SDL_EVENT_WINDOW_HIDDEN";
			case SDL_EVENT_WINDOW_EXPOSED:
				return "SDL_EVENT_WINDOW_EXPOSED";
			case SDL_EVENT_WINDOW_MOVED:
				return "SDL_EVENT_WINDOW_MOVED";
			case SDL_EVENT_WINDOW_RESIZED:
				return "SDL_EVENT_WINDOW_RESIZED";
			case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
				return "SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED";
			case SDL_EVENT_WINDOW_MINIMIZED:
				return "SDL_EVENT_WINDOW_MINIMIZED";
			case SDL_EVENT_WINDOW_MAXIMIZED:
				return "SDL_EVENT_WINDOW_MAXIMIZED";
			case SDL_EVENT_WINDOW_RESTORED:
				return "SDL_EVENT_WINDOW_RESTORED";
			case SDL_EVENT_WINDOW_MOUSE_ENTER:
				return "SDL_EVENT_WINDOW_MOUSE_ENTER";
			case SDL_EVENT_WINDOW_MOUSE_LEAVE:
				return "SDL_EVENT_WINDOW_MOUSE_LEAVE";
			case SDL_EVENT_WINDOW_FOCUS_GAINED:
				return "SDL_EVENT_WINDOW_FOCUS_GAINED";
			case SDL_EVENT_WINDOW_FOCUS_LOST:
				return "SDL_EVENT_WINDOW_FOCUS_LOST";
			case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
				return "SDL_EVENT_WINDOW_CLOSE_REQUESTED";
			case SDL_EVENT_WINDOW_TAKE_FOCUS:
				return "SDL_EVENT_WINDOW_TAKE_FOCUS";
			case SDL_EVENT_WINDOW_HIT_TEST:
				return "SDL_EVENT_WINDOW_HIT_TEST";
			case SDL_EVENT_WINDOW_ICCPROF_CHANGED:
				return "SDL_EVENT_WINDOW_ICCPROF_CHANGED";
			case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
				return "SDL_EVENT_WINDOW_DISPLAY_CHANGED";
			case SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED:
				return "SDL_EVENT_WINDOW_DISPLAY_SCALE_CHANGED";
			case SDL_EVENT_WINDOW_OCCLUDED:
				return "SDL_EVENT_WINDOW_OCCLUDED";
			case SDL_EVENT_WINDOW_ENTER_FULLSCREEN:
				return "SDL_EVENT_WINDOW_ENTER_FULLSCREEN";
			case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN:
				return "SDL_EVENT_WINDOW_LEAVE_FULLSCREEN";
			case SDL_EVENT_WINDOW_DESTROYED:
				return "SDL_EVENT_WINDOW_DESTROYED";
			case SDL_EVENT_WINDOW_PEN_ENTER:
				return "SDL_EVENT_WINDOW_PEN_ENTER";
			case SDL_EVENT_WINDOW_PEN_LEAVE:
				return "SDL_EVENT_WINDOW_PEN_LEAVE";
			case SDL_EVENT_KEY_DOWN:
				return "SDL_EVENT_KEY_DOWN";
			case SDL_EVENT_KEY_UP:
				return "SDL_EVENT_KEY_UP";
			case SDL_EVENT_TEXT_EDITING:
				return "SDL_EVENT_TEXT_EDITING";
			case SDL_EVENT_TEXT_INPUT:
				return "SDL_EVENT_TEXT_INPUT";
			case SDL_EVENT_KEYMAP_CHANGED:
				return "SDL_EVENT_KEYMAP_CHANGED";
			case SDL_EVENT_KEYBOARD_ADDED:
				return "SDL_EVENT_KEYBOARD_ADDED";
			case SDL_EVENT_KEYBOARD_REMOVED:
				return "SDL_EVENT_KEYBOARD_REMOVED";
			case SDL_EVENT_MOUSE_MOTION:
				return "SDL_EVENT_MOUSE_MOTION";
			case SDL_EVENT_MOUSE_BUTTON_DOWN:
				return "SDL_EVENT_MOUSE_BUTTON_DOWN";
			case SDL_EVENT_MOUSE_BUTTON_UP:
				return "SDL_EVENT_MOUSE_BUTTON_UP";
			case SDL_EVENT_MOUSE_WHEEL:
				return "SDL_EVENT_MOUSE_WHEEL";
			case SDL_EVENT_MOUSE_ADDED:
				return "SDL_EVENT_MOUSE_ADDED";
			case SDL_EVENT_MOUSE_REMOVED:
				return "SDL_EVENT_MOUSE_REMOVED";
			case SDL_EVENT_JOYSTICK_AXIS_MOTION:
				return "SDL_EVENT_JOYSTICK_AXIS_MOTION";
			case SDL_EVENT_JOYSTICK_BALL_MOTION:
				return "SDL_EVENT_JOYSTICK_BALL_MOTION";
			case SDL_EVENT_JOYSTICK_HAT_MOTION:
				return "SDL_EVENT_JOYSTICK_HAT_MOTION";
			case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
				return "SDL_EVENT_JOYSTICK_BUTTON_DOWN";
			case SDL_EVENT_JOYSTICK_BUTTON_UP:
				return "SDL_EVENT_JOYSTICK_BUTTON_UP";
			case SDL_EVENT_JOYSTICK_ADDED:
				return "SDL_EVENT_JOYSTICK_ADDED";
			case SDL_EVENT_JOYSTICK_REMOVED:
				return "SDL_EVENT_JOYSTICK_REMOVED";
			case SDL_EVENT_JOYSTICK_BATTERY_UPDATED:
				return "SDL_EVENT_JOYSTICK_BATTERY_UPDATED";
			case SDL_EVENT_JOYSTICK_UPDATE_COMPLETE:
				return "SDL_EVENT_JOYSTICK_UPDATE_COMPLETE";
			case SDL_EVENT_GAMEPAD_AXIS_MOTION:
				return "SDL_EVENT_GAMEPAD_AXIS_MOTION";
			case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
				return "SDL_EVENT_GAMEPAD_BUTTON_DOWN";
			case SDL_EVENT_GAMEPAD_BUTTON_UP:
				return "SDL_EVENT_GAMEPAD_BUTTON_UP";
			case SDL_EVENT_GAMEPAD_ADDED:
				return "SDL_EVENT_GAMEPAD_ADDED";
			case SDL_EVENT_GAMEPAD_REMOVED:
				return "SDL_EVENT_GAMEPAD_REMOVED";
			case SDL_EVENT_GAMEPAD_REMAPPED:
				return "SDL_EVENT_GAMEPAD_REMAPPED";
			case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:
				return "SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN";
			case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:
				return "SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION";
			case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:
				return "SDL_EVENT_GAMEPAD_TOUCHPAD_UP";
			case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:
				return "SDL_EVENT_GAMEPAD_SENSOR_UPDATE";
			case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:
				return "SDL_EVENT_GAMEPAD_UPDATE_COMPLETE";
			case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED:
				return "SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED";
			case SDL_EVENT_FINGER_DOWN:
				return "SDL_EVENT_FINGER_DOWN";
			case SDL_EVENT_FINGER_UP:
				return "SDL_EVENT_FINGER_UP";
			case SDL_EVENT_FINGER_MOTION:
				return "SDL_EVENT_FINGER_MOTION";
			case SDL_EVENT_CLIPBOARD_UPDATE:
				return "SDL_EVENT_CLIPBOARD_UPDATE";
			case SDL_EVENT_DROP_FILE:
				return "SDL_EVENT_DROP_FILE";
			case SDL_EVENT_DROP_TEXT:
				return "SDL_EVENT_DROP_TEXT";
			case SDL_EVENT_DROP_BEGIN:
				return "SDL_EVENT_DROP_BEGIN";
			case SDL_EVENT_DROP_COMPLETE:
				return "SDL_EVENT_DROP_COMPLETE";
			case SDL_EVENT_DROP_POSITION:
				return "SDL_EVENT_DROP_POSITION";
			case SDL_EVENT_AUDIO_DEVICE_ADDED:
				return "SDL_EVENT_AUDIO_DEVICE_ADDED";
			case SDL_EVENT_AUDIO_DEVICE_REMOVED:
				return "SDL_EVENT_AUDIO_DEVICE_REMOVED";
			case SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED:
				return "SDL_EVENT_AUDIO_DEVICE_FORMAT_CHANGED";
			case SDL_EVENT_SENSOR_UPDATE:
				return "SDL_EVENT_SENSOR_UPDATE";
			case SDL_EVENT_PEN_DOWN:
				return "SDL_EVENT_PEN_DOWN";
			case SDL_EVENT_PEN_UP:
				return "SDL_EVENT_PEN_UP";
			case SDL_EVENT_PEN_MOTION:
				return "SDL_EVENT_PEN_MOTION";
			case SDL_EVENT_PEN_BUTTON_DOWN:
				return "SDL_EVENT_PEN_BUTTON_DOWN";
			case SDL_EVENT_PEN_BUTTON_UP:
				return "SDL_EVENT_PEN_BUTTON_UP";
			case SDL_EVENT_CAMERA_DEVICE_ADDED:
				return "SDL_EVENT_CAMERA_DEVICE_ADDED";
			case SDL_EVENT_CAMERA_DEVICE_REMOVED:
				return "SDL_EVENT_CAMERA_DEVICE_REMOVED";
			case SDL_EVENT_CAMERA_DEVICE_APPROVED:
				return "SDL_EVENT_CAMERA_DEVICE_APPROVED";
			case SDL_EVENT_CAMERA_DEVICE_DENIED:
				return "SDL_EVENT_CAMERA_DEVICE_DENIED";
			case SDL_EVENT_RENDER_TARGETS_RESET:
				return "SDL_EVENT_RENDER_TARGETS_RESET";
			case SDL_EVENT_RENDER_DEVICE_RESET:
				return "SDL_EVENT_RENDER_DEVICE_RESET";
			case SDL_EVENT_POLL_SENTINEL:
				return "SDL_EVENT_POLL_SENTINEL";
			case SDL_EVENT_USER:
				return "SDL_EVENT_USER";
			case SDL_EVENT_LAST:
				return "SDL_EVENT_LAST";
			case SDL_EVENT_ENUM_PADDING:
				return "SDL_EVENT_ENUM_PADDING";
			default:
				break;
			}
			return "UNDEFINED";
		}

	private:
		SDL_Event* event;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
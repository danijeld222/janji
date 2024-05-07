#pragma once

#include "Event.h"

#include <sstream>

namespace Core
{
	class COREAPI KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		virtual int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class COREAPI KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return stringOutput.str();
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressed"; }

	private:
		int m_RepeatCount;
	};

	class COREAPI KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyReleased"; }
	};
}
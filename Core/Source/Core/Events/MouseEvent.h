#pragma once

#include "Event.h"

#include <sstream>

namespace Core
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(f32 x, f32 y)
			: m_MouseX(x), m_MouseY(y) {}

		inline f32 GetX() const { return m_MouseX; }
		inline f32 GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return stringOutput.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMoved"; }

		virtual i32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

	private:
		f32 m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(f32 xOffset, f32 yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline f32 GetXOffset() const { return m_XOffset; }
		inline f32 GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return stringOutput.str();
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseScrolled"; }

		virtual i32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

	private:
		f32 m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		inline i32 GetMouseButton() const { return m_Button; }

		virtual i32 GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

	protected:
		MouseButtonEvent(i32 button)
			: m_Button(button) {}

		i32 m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(i32 button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "MouseButtonPressedEvent: " << m_Button;
			return stringOutput.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonPressed"; }
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(i32 button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "MouseButtonReleasedEvent: " << m_Button;
			return stringOutput.str();
		}

		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseButtonReleased"; }
	};
}
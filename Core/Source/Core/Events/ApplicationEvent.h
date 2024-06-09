#pragma once

#include "Event.h"

#include <sstream>

namespace Core
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(u32 width, u32 height)
			: m_Width(width), m_Height(height) {}
	
		inline u32 GetWidth() const { return m_Width; }
		inline u32 GetHeight() const { return m_Height; }
	
		std::string ToString() const override
		{
			std::stringstream stringOutput;
			stringOutput << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return stringOutput.str();
		}
	
		static EventType GetStaticType() { return EventType::WindowResize; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowResize"; }
	
		virtual i32 GetCategoryFlags() const override { return EventCategoryApplication; }
	
	private:
		u32 m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
	
		static EventType GetStaticType() { return EventType::WindowClose; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "WindowClose"; }
	
		virtual i32 GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}
	
		static EventType GetStaticType() { return EventType::AppTick; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppTick"; }
	
		virtual i32 GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
	
		static EventType GetStaticType() { return EventType::AppUpdate; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppUpdate"; }
	
		virtual i32 GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}
	
		static EventType GetStaticType() { return EventType::AppRender; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "AppRender"; }
	
		virtual i32 GetCategoryFlags() const override { return EventCategoryApplication; }
	};
}
#pragma once

#include "pepch.h"

#include "Core.h"
#include "Core/Events/Event.h"

namespace ProjectEngine
{
	struct WindowProperties
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProperties(const std::string& title = "Project Engine",
							unsigned int width = 1280,
							unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		
		}
	};

	// Interface representing a desktop system based window
	class PROJECTENGINE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}
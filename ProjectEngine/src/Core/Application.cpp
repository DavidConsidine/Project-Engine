#include "Application.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Log.h"

namespace ProjectEngine
{

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			PE_TRACE(e);
			PE_INFO(e);
			PE_ERROR(e);
			PE_WARN(e);
			PE_CRITICAL(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			PE_INFO(e);
		}

		while (true);
	}
}
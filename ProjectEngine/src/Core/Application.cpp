#include "pepch.h"
#include "Application.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Log.h"

#include <GLFW/glfw3.h>

namespace ProjectEngine
{

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.5f, 1.0f, 0.25f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
#include <ProjectEngine.h>

class ExampleLayer : public ProjectEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (ProjectEngine::Input::IsKeyPressed(PE_KEY_TAB))
		{
			PE_INFO("Tab key is pressed. (poll)");
		}
	}

	void OnEvent(ProjectEngine::Event& event) override
	{
		if (event.GetEventType() == ProjectEngine::EventType::KeyPressed)
		{
			ProjectEngine::KeyPressedEvent& e = (ProjectEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == PE_KEY_TAB)
			{
				PE_INFO("Tab key is pressed. (event)");
			}
			PE_INFO("{0}", (char)e.GetKeyCode());
		}
	}
};



class Sandbox : public ProjectEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new ProjectEngine::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};


ProjectEngine::Application* ProjectEngine::CreateApplication()
{
	return new Sandbox();
}
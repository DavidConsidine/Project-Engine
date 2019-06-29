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
		PE_INFO("ExampleLayer::OnUpdate");
	}

	void OnEvent(ProjectEngine::Event& event) override
	{
		PE_TRACE("{0}", event);
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
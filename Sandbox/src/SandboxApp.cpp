#include <ProjectEngine.h>

class Sandbox : public ProjectEngine::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};


ProjectEngine::Application* ProjectEngine::CreateApplication()
{
	return new Sandbox();
}
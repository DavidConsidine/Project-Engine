#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern ProjectEngine::Application* ProjectEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		auto app = ProjectEngine::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Project Engine currently supports Windows only.
#endif
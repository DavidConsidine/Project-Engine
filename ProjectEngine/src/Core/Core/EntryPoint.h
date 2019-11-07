#pragma once

#ifdef PE_PLATFORM_WINDOWS

extern ProjectEngine::Application* ProjectEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		ProjectEngine::Log::Init();
		PE_CORE_WARN("Initialized Log!");
		int a = 5;
		PE_INFO("Hello! Var={0}", a);

		auto app = ProjectEngine::CreateApplication();
		app->Run();
		delete app;
	}
#else
	#error Project Engine currently supports Windows only.
#endif
#pragma once
#include "Core/Core/Core.h"

#ifdef PE_PLATFORM_WINDOWS

extern ProjectEngine::Application* ProjectEngine::CreateApplication();

	int main(int argc, char** argv)
	{
		ProjectEngine::Log::Init();

		PE_PROFILE_BEGIN_SESSION("Startup", "PEProfile-Startup.json");
		auto app = ProjectEngine::CreateApplication();
		PE_PROFILE_END_SESSION();
		PE_PROFILE_BEGIN_SESSION("Runtime", "PEProfile-Runtime.json");
		app->Run();
		PE_PROFILE_END_SESSION();
		PE_PROFILE_BEGIN_SESSION("Shutdown", "PEProfile-shutdown.json");
		delete app;
		PE_PROFILE_END_SESSION();
	}

#endif
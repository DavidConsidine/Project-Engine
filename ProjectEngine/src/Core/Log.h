#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace ProjectEngine
{
	class PROJECTENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define PE_CORE_TRACE(...)		::ProjectEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PE_CORE_INFO(...)		::ProjectEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PE_CORE_WARN(...)		::ProjectEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PE_CORE_ERROR(...)		::ProjectEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PE_CORE_CRITICAL(...)	::ProjectEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)


// Client log macros
#define PE_TRACE(...)			::ProjectEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PE_INFO(...)			::ProjectEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define PE_WARN(...)			::ProjectEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PE_ERROR(...)			::ProjectEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define PE_CRITICAL(...)		::ProjectEngine::Log::GetClientLogger()->critical(__VA_ARGS__)
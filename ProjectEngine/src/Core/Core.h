#pragma once

#include <memory>

#ifdef PE_PLATFORM_WINDOWS
	#if PE_DYNAMIC_LINK
		#ifdef PE_BUILD_DLL
			#define PROJECTENGINE_API __declspec(dllexport)
		#else
			#define PROJECTENGINE_API __declspec(dllimport)
		#endif
	#else
		#define PROJECTENGINE_API
	#endif
#else
	#error Project Engine currently supports Windows only.
#endif

#ifdef PE_DEBUG
	#define PE_ENABLE_ASSERTS
#endif

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) {if(!(x)) {PE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CORE_ASSERT(x, ...) {if(!(x)) {PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define PE_BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

namespace ProjectEngine
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}
#pragma once

#ifdef PE_PLATFORM_WINDOWS
	#ifdef PE_BUILD_DLL
		#define PROJECTENGINE_API __declspec(dllexport)
	#else
		#define PROJECTENGINE_API __declspec(dllimport)
	#endif
#else
	#error Project Engine currently supports Windows only.
#endif

#ifdef PE_ENABLE_ASSERTS
	#define PE_ASSERT(x, ...) {if(!x) {PE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PE_CORE_ASSERT(x, ...) {if(!x) {PE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PE_ASSERT(x, ...)
	#define PE_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

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

#define BIT(x) (1 << x)

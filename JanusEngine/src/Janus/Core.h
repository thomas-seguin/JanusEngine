#pragma once

#ifdef JN_PLATFORM_WINDOWS
	#ifdef JN_BUILD_DLL
		#define JANUS_API __declspec(dllexport)
	#else
		#define JANUS_API __declspec(dllimport)
	#endif // JN_BUILD_DLL
#else
	#error Janus only supports Windows!
#endif // JN_PLATFORM_WINDOWS

#define BIT(x) (1 << x)
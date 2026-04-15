#pragma once

#ifdef JN_PLATFORM_WINDOWS
#ifdef JN_DYNAMIC_LINK
	#ifdef JN_BUILD_DLL
		#define JANUS_API __declspec(dllexport)
	#else
		#define JANUS_API __declspec(dllimport)
	#endif // JN_BUILD_DLL
#else
	#define JANUS_API
#endif // JN_DYNAMIC_LINK
#else
	#error Janus only supports Windows!
#endif // JN_PLATFORM_WINDOWS

#ifdef JN_ENABLE_ASSERTS
#define JN_ASSERT(x, ...) {if(!(x)) {JN_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define JN_CORE_ASSERT(x, ...) {if(!(x)) {JN_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define JN_ASSERT(x, ...)
#define JN_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define JN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
workspace "JanusEngine"
	architecture "x64"
	startproject "Sandbox"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "JanusEngine"
	location "JanusEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines 
		{
			"JN_PLATFORM_WINDOWS",
			"JN_BUILD_DLL"
		}

		postbuildcommands 
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JN_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"JanusEngine/vendor/spdlog/include",
		"JanusEngine/src"
	}

	links 
	{
		"JanusEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines 
		{
			"JN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "JN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "JN_DIST"
		optimize "On"
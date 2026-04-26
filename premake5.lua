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

IncludeDir = {}
IncludeDir["GLFW"] = "JanusEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "JanusEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "JanusEngine/vendor/imgui"
IncludeDir["glm"] = "JanusEngine/vendor/glm"
IncludeDir["stb_image"] = "JanusEngine/vendor/stb_image"

group "Dependencies"
	include "JanusEngine/vendor/GLFW"
	include "JanusEngine/vendor/Glad"
	include "JanusEngine/vendor/imgui"
group ""

project "JanusEngine"
	location "JanusEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "jnpch.h"
	pchsource "JanusEngine/src/jnpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",

	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines 
		{
			"JN_PLATFORM_WINDOWS",
			"JN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "JN_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "JN_DIST"
		buildoptions "/MD"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"JanusEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{
		"JanusEngine"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines 
		{
			"JN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "JN_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "JN_DIST"
		buildoptions "/MD"
		optimize "on"

project "Janus-Editor"
	location "Janus-Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"JanusEngine/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links 
	{
		"JanusEngine"
	}

	filter "system:windows"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines 
		{
			"JN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "JN_DEBUG"
		buildoptions "/MDd"
		symbols "on"

	filter "configurations:Release"
		defines "JN_RELEASE"
		buildoptions "/MD"
		optimize "on"

	filter "configurations:Dist"
		defines "JN_DIST"
		buildoptions "/MD"
		optimize "on"
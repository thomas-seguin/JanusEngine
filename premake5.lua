workspace "JanusEngine"
	architecture "x64"
	startproject "Janus-Editor"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

defines { "YAML_CPP_STATIC_DEFINE" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "JanusEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "JanusEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "JanusEngine/vendor/imgui"
IncludeDir["glm"] = "JanusEngine/vendor/glm"
IncludeDir["stb_image"] = "JanusEngine/vendor/stb_image"
IncludeDir["entt"] = "JanusEngine/vendor/entt/include"
IncludeDir["yaml_cpp"] = "JanusEngine/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "JanusEngine/vendor/ImGuizmo"


group "Dependencies"
	include "JanusEngine/vendor/GLFW"
	include "JanusEngine/vendor/Glad"
	include "JanusEngine/vendor/imgui"
	include "JanusEngine/vendor/yaml-cpp"
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
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.h",
		"%{prj.name}/vendor/ImGuizmo/ImGuizmo.cpp",
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
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"yaml-cpp",
		"opengl32.lib"
	}

filter "files:JanusEngine/vendor/ImGuizmo/**.cpp"
    enablepch "off"

	filter "system:windows"
		systemversion "latest"
		buildoptions {"/utf-8"}

		defines 
		{
			"JN_PLATFORM_WINDOWS",
			"JN_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"IMGUI_DEFINE_MATH_OPERATORS" 
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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}"
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
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
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
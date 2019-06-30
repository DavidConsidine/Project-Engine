workspace "ProjectEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ProjectEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "ProjectEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "ProjectEngine/vendor/imgui"

group "Dependencies"
	include "ProjectEngine/vendor/GLFW"
	include "ProjectEngine/vendor/Glad"
	include "ProjectEngine/vendor/imgui"
group ""

project "ProjectEngine"
	location "ProjectEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pepch.h"
	pchsource "ProjectEngine/src/pepch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PE_PLATFORM_WINDOWS",
			"PE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PE_DIST"
		runtime "Release"
		optimize "On"
	

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"ProjectEngine/vendor/spdlog/include",
		"ProjectEngine/src"
	}

	links
	{
		"ProjectEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"PE_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PE_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "PE_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "PE_DIST"
		runtime "Release"
		optimize "On"
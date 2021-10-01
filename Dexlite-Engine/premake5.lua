project "Dexlite-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	filter "system:windows"
		systemversion "latest"
	filter {}
	
	targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
	objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

	files
	{
		"%{prj.location}/src/**"
	}

	sysincludedirs
	{
		"%{IncludeDir.include}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
        "%{IncludeDir.stb_image}",
		"%{IncludeDir.tinygltf}",
		"%{IncludeDir.spdlog}"
	}

	links
	{        
		"glad",
		"glfw",
		"imgui",
		"tinygltf"
	}

	defines
	{
		"GLM_FORCE_LEFT_HANDED",
		"GLFW_INCLUDE_NONE",
		"STB_IMAGE_IMPLEMENTATION",
		"STB_IMAGE_WRITE_IMPLEMENTATION"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
	filter {}

	filter "configurations:Release"
		runtime "Release"
		optimize "Speed"
		inlining "Auto"
	filter {}

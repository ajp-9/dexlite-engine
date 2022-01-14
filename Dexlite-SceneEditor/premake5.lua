project "Dexlite-SceneEditor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    filter "system:windows"
        systemversion "latest"
    filter {}

    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**",
        "%{prj.location}/vendor/**"
    }

    sysincludedirs
    {
        "%{wks.location}/Dexlite-Engine/src",

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
        "Dexlite-Engine",
        "glad",
        "glfw",
        "imgui",
        "tinygltf"
    }

    filter {"system:windows", "toolset:gcc"}
        links
        {
            "gdi32",
            "opengl32.lib",
            "imm32"
        }
    filter {}

    filter "system:macosx"
        links
        {
            "Cocoa.framework",
            "IOKit.framework",
            "CoreFoundation.framework"
        }
    filter {}

    filter "system:linux"
        links
        {
            "GL",
            "X11",
            "pthread",
            "Xrandr"    
        }
    filter {}

    defines
    {
        "GLM_FORCE_LEFT_HANDED",
        "GLFW_INCLUDE_NONE"
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

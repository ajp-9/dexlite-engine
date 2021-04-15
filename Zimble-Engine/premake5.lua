project "Zimble-Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**"
    }

    sysincludedirs
    {
        "%{IncludeDir.includes}",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.assimp}"
    }

    syslibdirs
    {
        "%{LibDir.SDL2}",
        "%{LibDir.assimp}"
    }

    links
    {
        "glad",
        "imgui"
    }

    filter "system:windows"
        links
        {
            "%{WindowsLibrary.SDL2}",
            "%{WindowsLibrary.assimp}"
        }
    filter {}

    filter "system:mac"
        links
        {
            "%{MacLibrary.SDL2}",
            "%{MacLibrary.assimp}",
            "%{MacLibrary.zlibstatic}"
        }
    filter {}

    defines
    {
        "SDL_MAIN_HANDLED",
        "GLM_FORCE_LEFT_HANDED"
    }

    filter "system:windows"
        systemversion "latest"
    filter {}

    filter "configurations:Debug"
        optimize "Off"
    filter {}

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"
    filter {}

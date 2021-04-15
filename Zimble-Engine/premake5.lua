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

    links
    {        
        "glad",
        "SDL2",
        "imgui",
        "assimp"
    }

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

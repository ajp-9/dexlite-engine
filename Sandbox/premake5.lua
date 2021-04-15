project "SandBox"
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
        "%{wks.location}/Zimble-Engine/src",

        "%{IncludeDir.includes}",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.assimp}"
    }

    links
    {
        "Zimble-Engine"
    }

    defines
    {
        "SDL_MAIN_HANDLED",
        "GLM_FORCE_LEFT_HANDED"
    }

    filter "configurations:Debug"
        optimize "Off"

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"

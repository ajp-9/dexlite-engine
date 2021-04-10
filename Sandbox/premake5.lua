project "SandBox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    filter "system:windows"
        systemversion "latest"

    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**",
        "%{prj.location}/vendor/**"
    }

    sysincludedirs
    {
        "%{wks.location}/Nimble-Engine/src",

        "%{IncludeDir.includes}",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "Nimble-Engine",

        "glad",
        "imgui",
        "SDL2"
    }

    defines
    {
        "SDL_MAIN_HANDLED"
    }

    filter "configurations:Debug"
        optimize "Off"

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"

project "Nimble-Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**",
        "%{prj.location}/vendor/**"
    }

    sysincludedirs
    {
        "%{IncludeDir.includes}",
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}"
    }

    syslibdirs
    {
        "%{LibDir.SDL2}"
    }

    links
    {
        "SDL2-static.lib",
        
        "glad",
        "imgui"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        optimize "Off"

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"

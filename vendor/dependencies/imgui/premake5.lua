project "imgui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**",
        "%{prj.location}/include/**"
    }

    includedirs
    {
        "%{prj.location}/include/imgui"
    }

    sysincludedirs
    {
        "%{IncludeDir.SDL2}",
        "%{IncludeDir.glad}"
    }

    syslibdirs
    {
        "%{LibDir.SDL2}"
    }

    links
    {
        "SDL2-static.lib",
        
        "glad"
    }

    filter "system:windows"
    systemversion "latest"

    filter "configurations:Debug"
        optimize "Off"

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"

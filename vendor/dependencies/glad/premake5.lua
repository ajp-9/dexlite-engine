project "glad"
    kind "StaticLib"
    language "C"

    filter "system:windows"
        systemversion "latest"
    filter {}
    
    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**",
        "%{prj.location}/include/**"
    }

    sysincludedirs
    {
        "%{prj.location}/include"
    }

    filter "configurations:Debug"
        optimize "Off"
    filter {}

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"
    filter {}

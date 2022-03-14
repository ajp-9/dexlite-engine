project "imguizmo"
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
        "%{prj.location}/src/**",
        "%{prj.location}/include/**"
    }

    includedirs
    {
        "%{prj.location}/include",
        "%{IncludeDir.imgui}/imgui"
    }

    sysincludedirs
    {
        "%{IncludeDir.glad}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.imgui}"
    }

    links
    {        
        "glad",
        "glfw",
        "imgui"
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

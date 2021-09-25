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
        "%{wks.location}/Dexterous-Engine/src",

        "%{IncludeDir.include}",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}"
    }

    links
    {
        "Dexterous-Engine"
    }

    defines
    {
        "SDL_MAIN_HANDLED",
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

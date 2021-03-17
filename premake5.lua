workspace "Nimble-Engine"
    architecture "x64"
    startproject "SandBox"

    configurations {"Debug", "Release"}

project "Nimble-Engine"
    location "Nimble-Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("%{prj.name}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.name}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",
        "%{wks.location}/Nimble-Engine/vendor/**"
    }

    sysincludedirs
    {
        "src",
        "%{wks.location}/linking/include/"
    }

    syslibdirs
    {
        "%{wks.location}/linking/libs"
    }

    links
    {
        "SDL2-static.lib"
    }

    filter "configurations:Debug"
        optimize "Off"

    filter "configurations:Release"
        optimize "On"

project "SandBox"
    location "SandBox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("%{prj.name}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.name}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp"
    }

    sysincludedirs
    {
        "src",
        "%{wks.location}/linking/include/",
        "%{wks.location}/Nimble-Engine/src"
    }
    
    syslibdirs
    {
        "%{wks.location}/linking/libs"
    }

    links
    {
        "Nimble-Engine",
        "winmm.lib",
        "imm32.lib",
        "version.lib",
        "setupapi.lib"
    }

    defines
    {
        "SDL_MAIN_HANDLED"
    }

    filter "configurations:Debug"
        optimize "Off"

    filter "configurations:Release"
        optimize "On"
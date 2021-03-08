workspace "Zip-Engine"
    architecture "x64"
    startproject "Game"

    configurations {"Debug", "Release"}

project "Zip-Engine"
    location "Zip-Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("%{prj.name}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.name}/intermediates/%{cfg.buildcfg}")

    files
    {
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",
        "%{wks.location}/Zip-Engine/vendor/**"
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

project "Game"
    location "Game"
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
        "%{wks.location}/Zip-Engine/src"
    }
    
    syslibdirs
    {
        "%{wks.location}/linking/libs"
    }

    links
    {
        "Zip-Engine",
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
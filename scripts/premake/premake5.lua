workspace "Zip-Engine"
    architecture "x64"

    configurations {"Debug", "Release"}

outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "Zip-Engine"
    location "../../Zip-Engine"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir "/%{prj.name}")
    objdir ("bin/" .. outputdir "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**"
    }

    include
    {
        "linking/include/"
    }

    filter "configurations:Debug"
        optimize "On"

    filter "configurations:Release"
        optimize "On"

project "Game"
    location "../../Game"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir "/%{prj.name}")
    objdir ("bin/" .. outputdir "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**"
    }

    include
    {
        "linking/include/"
    }

    links
    {
        "Zip-Engine"
    }

    filter "configurations:Debug"
        optimize "On"

    filter "configurations:Release"
        optimize "On"
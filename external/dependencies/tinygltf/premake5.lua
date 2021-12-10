project "tinygltf"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    filter "system:windows"
        systemversion "latest"
    filter {}
    filter "system:macosx"
        systemversion "latest"
    filter {}
    filter "system:linux"
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
        "%{IncludeDir.include}",
        "%{IncludeDir.stb_image}"
    }

    sysincludedirs
    {
        "%{prj.location}/include"
    }

    links
    {
        "stb_image"
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

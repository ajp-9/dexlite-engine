project "BulletDynamics"
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
        "%{prj.location}/bullet3/**"
    }

    includedirs
    {
        "%{prj.location}/bullet3/",

        "%{IncludeDir.bullet3}/bullet3",
        "%{IncludeDir.bullet3_LinearMath}",
        "%{IncludeDir.bullet3_BulletCollision}"
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

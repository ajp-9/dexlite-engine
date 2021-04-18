project "zlib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++14"

    filter "system:windows"
        systemversion "latest"
    filter {}
    
    targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
    objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

    files
    {
        "adler32.c",
        "compress.c",
        "crc32.c",
        "deflate.c",
        "gzclose.c",
        "gzlib.c",
        "gzread.c",
        "gzwrite.c",
        "inflate.c",
        "infback.c",
        "inftrees.c",
        "inffast.c",
        "trees.c",
        "uncompr.c",
        "zutil.c",
        "zconf.h",
        "zlib.h",
        "crc32.h",
        "deflate.h",
        "gzguts.h",
        "inffast.h",
        "inffixed.h",
        "inflate.h",
        "inftrees.h",
        "trees.h",
        "zutil.h"
    }

    sysincludedirs
    {
        "%{prj.location}",
        "%{prj.location}/../",
        "%{prj.location}/../../",
        "%{prj.location}/../../code"
    }

    defines
    {
        "NDEBUG",
        "UNICODE",
        "_UNICODE",
        "NO_FSEEKO",
        "_CRT_SECURE_NO_DEPRECATE",
        "_CRT_NONSTDC_NO_DEPRECATE"
    }

    filter "system:windows"
        defines
        {
            "WIN32",
            "_WINDOWS",
            "WIN32_LEAN_AND_MEAN"
        }
    filter {}

    filter "configurations:Debug"
        optimize "Off"
    filter {}

    filter "configurations:Release"
        optimize "Speed"
        inlining "Auto"
    filter {}

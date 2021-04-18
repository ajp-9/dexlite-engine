workspace "Dexterous-Engine"
    architecture "x64"
    startproject "SandBox"

    configurations {"Debug", "Release"}

    filter "system:Windows"
        system "windows"
    filter {}

IncludeDir = {}
IncludeDir["include"] = "%{wks.location}/vendor/include"
IncludeDir["SDL2"] = "%{wks.location}/vendor/dependencies/SDL2/include"
IncludeDir["glad"] = "%{wks.location}/vendor/dependencies/glad/include"
IncludeDir["imgui"] = "%{wks.location}/vendor/dependencies/imgui/include"
IncludeDir["assimp"] = "%{wks.location}/vendor/dependencies/assimp/include"
IncludeDir["zlib"] = "%{wks.location}/vendor/dependencies/assimp/contrib/zlib"

group "Dependencies"
    include "vendor/dependencies/assimp"
    include "vendor/dependencies/assimp/contrib/zlib"
    include "vendor/dependencies/glad"
    include "vendor/dependencies/SDL2"
    include "vendor/dependencies/imgui"
group ""

include "Dexterous-Engine"
include "Sandbox"

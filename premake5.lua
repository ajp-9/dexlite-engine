workspace "Zimble-Engine"
    architecture "x64"
    startproject "SandBox"

    configurations {"Debug", "Release"}

IncludeDir = {}
IncludeDir["includes"] = "%{wks.location}/vendor/includes"
IncludeDir["SDL2"] = "%{wks.location}/vendor/dependencies/SDL2/include"
IncludeDir["glad"] = "%{wks.location}/vendor/dependencies/glad/include"
IncludeDir["imgui"] = "%{wks.location}/vendor/dependencies/imgui/include"
IncludeDir["assimp"] = "%{wks.location}/vendor/dependencies/assimp/include"

group "Dependencies"
    include "vendor/dependencies/glad"
    include "vendor/dependencies/SDL2"
    include "vendor/dependencies/imgui"
    include "vendor/dependencies/assimp"
group ""

include "Zimble-Engine"
include "Sandbox"

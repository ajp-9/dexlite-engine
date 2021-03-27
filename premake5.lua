workspace "Nimble-Engine"
    architecture "x64"
    startproject "SandBox"

    configurations {"Debug", "Release"}

IncludeDir = {}
IncludeDir["includes"] = "%{wks.location}/vendor/includes"
IncludeDir["SDL2"] = "%{wks.location}/vendor/dependencies/SDL2/include"
IncludeDir["glad"] = "%{wks.location}/vendor/dependencies/glad/include"

LibDir = {}
LibDir["SDL2"] = "%{wks.location}/vendor/dependencies/SDL2/lib"

group "Dependencies"
    include "vendor/dependencies/glad"
group ""

include "Nimble-Engine"
include "Sandbox"
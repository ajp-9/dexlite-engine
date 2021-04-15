workspace "Zimble-Engine"
    architecture "x64"
    startproject "SandBox"

    configurations {"Debug", "Release"}

    filter "system:Windows"
        system "windows"
  
    filter "system:Mac"
        system "macosx"

IncludeDir = {}
IncludeDir["includes"] = "%{wks.location}/vendor/includes"
IncludeDir["SDL2"] = "%{wks.location}/vendor/dependencies/SDL2/include"
IncludeDir["glad"] = "%{wks.location}/vendor/dependencies/glad/include"
IncludeDir["imgui"] = "%{wks.location}/vendor/dependencies/imgui/include"
IncludeDir["assimp"] = "%{wks.location}/vendor/dependencies/assimp/include"

LibDir = {}
LibDir["SDL2"] = "%{wks.location}/vendor/dependencies/SDL2/lib"
LibDir["assimp"] = "%{wks.location}/vendor/dependencies/assimp/lib"

filter "system:windows"
    WindowsLibrary = {}
    WindowsLibrary["SDL2"] = "SDL2.lib"
    WindowsLibrary["assimp"] = "assimp.lib"
    WindowsLibrary["zlibstatic"] = "zlibstatic.lib" -- needed for assimp
filter {}

filter "system:mac"
    MacLibrary = {}
    MacLibrary["SDL2"] = "SDL2.a"
    MacLibrary["assimp"] = "assimp.a"
    MacLibrary["zlibstatic"] = "zlibstatic.a" -- needed for assimp
filter {}

group "Dependencies"
    include "vendor/dependencies/glad"
    include "vendor/dependencies/imgui"
group ""

include "Zimble-Engine"
include "Sandbox"

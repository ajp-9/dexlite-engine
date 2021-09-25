workspace "Dexterous-Engine"
	architecture "x64"
	startproject "SandBox"

	configurations {"Debug", "Release"}

	filter "system:Windows"
		system "windows"
	filter {}

IncludeDir = {}
IncludeDir["include"] = "%{wks.location}/external/include"
IncludeDir["glfw"] = "%{wks.location}/external/dependencies/glfw/include"
IncludeDir["glad"] = "%{wks.location}/external/dependencies/glad/include"
IncludeDir["imgui"] = "%{wks.location}/external/dependencies/imgui/include"

group "Dependencies"
	include "external/dependencies/glfw"
	include "external/dependencies/glad"
	include "external/dependencies/imgui"
group ""

include "Dexterous-Engine"
include "Sandbox"

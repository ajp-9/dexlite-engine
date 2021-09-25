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
IncludeDir["stb_image"] = "%{wks.location}/external/dependencies/stb_image/include"
IncludeDir["tinygltf"] = "%{wks.location}/external/dependencies/tinygltf/include"

group "Dependencies"
	include "external/dependencies/glfw"
	include "external/dependencies/glad"
	include "external/dependencies/imgui"
	include "external/dependencies/stb_image"
	include "external/dependencies/tinygltf"
group ""

include "Dexterous-Engine"
include "Sandbox"

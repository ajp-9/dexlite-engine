workspace "Dexlite-Engine"
	architecture "x64"
	startproject "Dexlite-SceneEditor"

	configurations {"Debug", "Release"}

	filter "system:Windows"
		system "windows"
	filter {}

IncludeDir = {}
IncludeDir["include"] = "%{wks.location}/external/include"
IncludeDir["glfw"] = "%{wks.location}/external/dependencies/glfw/include"
IncludeDir["glad"] = "%{wks.location}/external/dependencies/glad/include"
IncludeDir["imgui"] = "%{wks.location}/external/dependencies/imgui/include"
IncludeDir["imguizmo"] = "%{wks.location}/external/dependencies/imguizmo/include"
IncludeDir["stb_image"] = "%{wks.location}/external/dependencies/stb_image/include"
IncludeDir["tinygltf"] = "%{wks.location}/external/dependencies/tinygltf/include"
IncludeDir["spdlog"] = "%{wks.location}/external/dependencies/spdlog/include"

group "Dependencies"
	include "external/dependencies/glfw"
	include "external/dependencies/glad"
	include "external/dependencies/imgui"
	include "external/dependencies/imguizmo"
	include "external/dependencies/stb_image"
	include "external/dependencies/tinygltf"
	include "external/dependencies/spdlog"
group ""

include "Dexlite-Engine"
include "Dexlite-SceneEditor"
include "Sandbox"

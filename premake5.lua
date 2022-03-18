workspace "Dexlite-Engine"
	architecture "x64"
	startproject "Dexlite-SceneEditor"

	configurations {"Debug", "Release"}

	filter "system:Windows"
		system "windows"
	filter {}

IncludeDir = {}
IncludeDir["include"]   = "%{wks.location}/external/include"
IncludeDir["glfw"]      = "%{wks.location}/external/dependencies/glfw/include"
IncludeDir["glad"]      = "%{wks.location}/external/dependencies/glad/include"
IncludeDir["imgui"]     = "%{wks.location}/external/dependencies/imgui/include"
IncludeDir["imguizmo"]  = "%{wks.location}/external/dependencies/imguizmo/include"
IncludeDir["stb_image"] = "%{wks.location}/external/dependencies/stb_image/include"
IncludeDir["tinygltf"]  = "%{wks.location}/external/dependencies/tinygltf/include"
IncludeDir["spdlog"]    = "%{wks.location}/external/dependencies/spdlog/include"

IncludeDir["bullet3"]                 = "%{wks.location}/external/dependencies/bullet3/include"
IncludeDir["bullet3_LinearMath"]      = "%{wks.location}/external/dependencies/bullet3/LinearMath/bullet3"
IncludeDir["bullet3_BulletCollision"] = "%{wks.location}/external/dependencies/bullet3/BulletCollision/bullet3"
IncludeDir["bullet3_BulletDynamics"]  = "%{wks.location}/external/dependencies/bullet3/BulletDynamics/bullet3"

group "Dependencies"
	include "external/dependencies/glfw"
	include "external/dependencies/glad"
	include "external/dependencies/imgui"
	include "external/dependencies/imguizmo"
	include "external/dependencies/stb_image"
	include "external/dependencies/tinygltf"
	include "external/dependencies/spdlog"

	group "Dependencies/bullet3"
		include "external/dependencies/bullet3/LinearMath"
		include "external/dependencies/bullet3/BulletCollision"
		include "external/dependencies/bullet3/BulletDynamics"
	group "Dependencies"
group ""

include "Dexlite-Engine"
include "Dexlite-SceneEditor"
include "Sandbox"

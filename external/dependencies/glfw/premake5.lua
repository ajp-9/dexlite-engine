project "glfw"
	kind "StaticLib"
	language "C"

	targetdir ("%{prj.location}/bin/%{cfg.buildcfg}")
	objdir ("%{prj.location}/intermediates/%{cfg.buildcfg}")

	files
	{
		"include/GLFW/glfw3.h",
		"include/GLFW/glfw3native.h",
		"src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
	}

	filter "system:windows"
		systemversion "latest"

		files
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_monitor.c",
			"src/win32_time.c",
			"src/win32_thread.c",
			"src/win32_window.c",
			"src/wgl_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
	filter {}

	filter "system:mac"
		systemversion "latest"
		
		files
		{
			"src/cocoa_init.c",
			"src/cocoa_monitor.c",
			"src/cocoa_window.c",
			"src/cocoa_time.c",
			"src/posix_module.c"
			"src/posix_thread.c",
			"src/glx_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c"
		}

		defines
		{
			"_GLFW_COCOA"
		}
	filter {}

	filter "system:linux"
		--pic "On"

		systemversion "latest"
		
		files
		{
			"src/x11_init.c",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_time.c",
			"src/posix_thread.c",
			"src/glx_context.c",
			"src/egl_context.c",
			"src/osmesa_context.c",
			"src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}
	filter {}

	filter "configurations:Debug"
			runtime "Debug"
			symbols "on"
	filter {}

	filter "configurations:Release"
			runtime "Release"
			optimize "Speed"
			inlining "Auto"
	filter {}

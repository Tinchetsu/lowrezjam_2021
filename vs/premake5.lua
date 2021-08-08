workspace "Game"
	configurations { "Debug","Debug.DLL", "Release", "Release.DLL" }
	platforms { "x64"}

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
		
	filter "configurations:Debug.DLL"
		defines { "DEBUG" }
		symbols "On"

	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter "configurations:Release.DLL"
		defines { "NDEBUG" }
		optimize "On"	
		
	filter { "platforms:x64" }
		architecture "x86_64"
		
	targetdir "bin/%{cfg.buildcfg}/"
	
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}
		
project "raylib"
		filter "configurations:Debug.DLL OR Release.DLL"
			kind "SharedLib"
			defines {"BUILD_LIBTYPE_SHARED"}
			
		filter "configurations:Debug OR Release"
			kind "StaticLib"
			
		filter "action:vs*"
			defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
			links {"winmm"}
			
		filter "action:gmake*"
			links {"pthread", "GL", "m", "dl", "rt", "X11"}
			
		filter{}
		
		location "build"
		language "C++"
		targetdir "bin/%{cfg.buildcfg}"
		cppdialect "C++17"
		
		includedirs { "../lib/raylib/src", "../lib/raylib/src/external/glfw/include"}
		vpaths 
		{
			["Header Files"] = { "../lib/raylib/src/**.h"},
			["Source Files/*"] = {"../lib/raylib/src/**.c"},
		}
		files {"../lib/raylib/src/*.h", "../lib/raylib/src/*.c"}
		
project "Game"
	kind "ConsoleApp"
	location "%{wks.name}"
	language "C++"
	targetdir "bin/%{cfg.buildcfg}"
	cppdialect "C++17"
	
	includedirs {"../src"}
	vpaths 
	{
		["Header Files"] = { "../src/**.h"},
		["Source Files"] = {"../src/**.c", "../src/**.cpp"},
	}
	files {"../src/*.c", "../src/*.cpp", "../src/*.h"}

	links {"raylib"}
	
	includedirs { "%{wks.name}", "../lib/raylib/src" }
	defines{"PLATFORM_DESKTOP", "GRAPHICS_API_OPENGL_33"}
	
	filter "action:vs*"
		defines{"_WINSOCK_DEPRECATED_NO_WARNINGS", "_CRT_SECURE_NO_WARNINGS", "_WIN32"}
		dependson {"raylib"}
		links {"raylib.lib", "winmm", "kernel32"}
		libdirs {"bin/%{cfg.buildcfg}"}
		
	filter "action:gmake*"
		links {"pthread", "GL", "m", "dl", "rt", "X11"}

-- premake5.exe vs2019
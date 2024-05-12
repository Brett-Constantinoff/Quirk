local vulkanSdk = os.getenv("VULKAN_SDK")
local vulkanInclude = vulkanSdk.."/include"
local vulkanLib = vulkanSdk.."/lib/vulkan-1.lib"

workspace "Quirk"
    configurations { "Debug", "Release" }
    startproject "QuirkEditor"
    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "QuirkEditor"
    location "src"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	architecture "x64"

    targetdir "src/bin/%{cfg.buildcfg}"
    objdir "src/bin-int/%{cfg.buildcfg}"

    includedirs 
    {
	vulkanInclude
    }
    
    files 
    { 
	"src/**.cpp",
        "src/**.hpp",
    }

    links 
    { 
	vulkanLib
    }

    filter "system:windows"
        defines 
        { 
            "_WINDOWS" 
        }
        links
        {
 	     "OpengL32"
        }
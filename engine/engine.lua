local vulkanSdk = os.getenv("VULKAN_SDK")
local vulkanInclude = vulkanSdk.."/include"
local vulkanLib = vulkanSdk.."/lib/vulkan-1.lib"

project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    architecture "x64"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    includedirs 
    {
        vulkanInclude,
        "../thirdParty/glfw/include/",
        "../thirdParty/logging/include/",
    }

    files 
    { 
        "**.cpp",
        "**.hpp",
    }

    links 
    { 
        vulkanLib,
        "Glfw",
    }

    filter "system:windows"
        defines 
        { 
            "_WINDOWS" 
        }
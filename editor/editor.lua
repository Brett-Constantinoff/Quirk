local vulkanSdk = os.getenv("VULKAN_SDK")
local vulkanInclude = vulkanSdk.."/include"
local vulkanLib = vulkanSdk.."/lib/vulkan-1.lib"

project "Editor"
    kind "ConsoleApp"
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
        "../engine/"
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
        "Engine"
    }

    filter "system:windows"
        defines 
        { 
            "_WINDOWS" 
        }

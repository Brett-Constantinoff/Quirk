project "Engine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    architecture "x64"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    includedirs 
    {
        "../thirdParty/Glfw/include/",
        "../thirdParty/logging/include/",
        "../thirdParty/glad/include/",
        "../thirdParty/gui/",
    }

    files 
    { 
        "**.cpp",
        "**.hpp",
    }

    links 
    { 
        "Glfw",
        "Glad",
        "Imgui",
        "OpengL32",
    }
    			
    filter "system:windows"
        systemversion "latest"
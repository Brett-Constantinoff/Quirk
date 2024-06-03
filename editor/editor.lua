project "Editor"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    architecture "x64"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    includedirs 
    {
        "../thirdParty/logging/include/",
        "../thirdParty/Glfw/include/",
        "../thirdParty/glad/include/",
        "../thirdParty/gui/",
        "../thirdParty/glm/",
        "../engine/"
    }

    files 
    { 
        "**.cpp",
        "**.hpp",
    }

    links 
    { 
        "Glm",
        "Glfw",
        "Glad",
        "Imgui",
        "OpengL32",
        "Engine",
    }

    filter "system:windows"
        systemversion "latest"
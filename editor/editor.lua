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
        "../thirdParty/assimp/include/",
        "../thirdParty/entt/src/",
        "../engine/"
    }

    files 
    { 
        "**.cpp",
        "**.hpp",
        "**.h",
        "**.c",
    }

    links 
    { 
        "Glm",
        "Glfw",
        "Glad",
        "Imgui",
        "../thirdParty/assimp/lib/assimp-vc142-mt", 
        "../thirdParty/assimp/lib/zlibstatic",
        "OpengL32",
        "Engine",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
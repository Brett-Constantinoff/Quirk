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
        "../thirdParty/glm/",
        "../thirdParty/assimp/include/",
        "../thirdParty/entt/src/",
    }

    files 
    { 
        "**.cpp",
        "**.h",
        "**.c",
        "**.hpp",
        '**.inl',
    }

    links 
    { 
        "Glm",
        "Glfw",
        "Glad",
        "Imgui",
        "OpengL32",
        "../thirdParty/assimp/lib/assimp-vc142-mt", 
        "../thirdParty/assimp/lib/zlibstatic",
    }
    			
    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
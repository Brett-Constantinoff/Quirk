project "Editor"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++20"
    architecture "x64"

    targetdir "%{wks.location}/bin/%{cfg.buildcfg}"
    objdir "%{wks.location}/bin-int/%{cfg.buildcfg}"

    includedirs 
    {
        "%{wks.location}/thirdParty/logging/include/",
        "%{wks.location}/thirdParty/Glfw/include/",
        "%{wks.location}/thirdParty/glad/include/",
        "%{wks.location}/thirdParty/gui/",
        "%{wks.location}/thirdParty/glm/",
        "%{wks.location}/thirdParty/assimp/include/",
        "%{wks.location}/thirdParty/enttEcs/single_include/",
        "%{wks.location}/thirdParty/uuids/include",
        "%{wks.location}/engine/"
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
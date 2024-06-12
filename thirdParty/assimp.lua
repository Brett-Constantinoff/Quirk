project "assimp"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    architecture "x86_64"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    includedirs 
    {
        "thirdParty/assimp/include",
        "thirdParty/assimp/code"
    }

    files 
    {
        "thirdParty/assimp/include/**.h",
        "thirdParty/assimp/code/**.cpp",
        "thirdParty/assimp/contrib/irrXML/*.cpp",
        "thirdParty/assimp/contrib/irrXML/*.h",
        "thirdParty/assimp/contrib/zlib/*.c",
        "thirdParty/assimp/contrib/zlib/*.h",
        "thirdParty/assimp/contrib/unzip/*.c",
        "thirdParty/assimp/contrib/unzip/*.h"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
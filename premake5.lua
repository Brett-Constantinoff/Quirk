workspace "Quirk"
    configurations { "Debug", "Release" }
    startproject "Editor"
    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }


include "engine/engine.lua"
include "editor/editor.lua"
include "thirdParty/glfw.lua"
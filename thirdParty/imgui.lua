project "Imgui"
    kind "StaticLib"
    language "C++"
    architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"
    
    includedirs { "gui/", "gui/backends/", "Glfw/include/" }

    files 
    { 
        "gui/imgui.cpp",
        "gui/imgui_draw.cpp",
        "gui/imgui_tables.cpp",
        "gui/imgui_widgets.cpp",
        "gui/imgui_demo.cpp",  --do we want to show the demo window?
        "gui/backends/imgui_impl_glfw.cpp",
        "gui/backends/imgui_impl_opengl3.cpp",
        "gui/backends/imgui_impl_glfw.h",
        "gui/backends/imgui_impl_opengl3.h",
        "gui/imgui.h",
        "gui/imgui_internal.h",
        "gui/imconfig.h",
        "gui/imstb_rectpack.h",
        "gui/imstb_textedit.h",
        "gui/imstb_truetype.h"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

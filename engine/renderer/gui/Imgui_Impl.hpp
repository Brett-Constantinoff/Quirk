#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Quirk::Engine::Renderer::Gui
{
    // This is just a wrapper around our own Imgui implementation
    // so any custom designs will go here
    class Imgui_Impl
    {
    public:
        Imgui_Impl() = delete;
        Imgui_Impl(const Imgui_Impl&) = delete;
        Imgui_Impl& operator=(const Imgui_Impl&) = delete;
        ~Imgui_Impl();

        static void setup(GLFWwindow* currentContext);
        static void updateFrame();
        static void renderFrame();
    };
}

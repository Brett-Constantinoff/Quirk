#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Quirk::Engine::Renderer::Gui
{
    // This is just a wrapper around our own Imgui implementation
    // so any custom designs will go here
    class ImguiImpl
    {
    public:
        ImguiImpl() = default;
        ~ImguiImpl() = default;

        static void init(GLFWwindow* currentContext);
        static void shutdown();
        static void updateFrame();
        static void renderFrame();
    };
} // namespace Quirk::Engine::Renderer::Gui

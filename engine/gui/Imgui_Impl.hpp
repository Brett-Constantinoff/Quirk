#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace Quirk::Engine::Gui
{
    class Imgui_Impl
    {
    public:
        Imgui_Impl(const Imgui_Impl&) = delete;
        Imgui_Impl& operator=(const Imgui_Impl&) = delete;

        static Imgui_Impl& getInstance()
        {
            static Imgui_Impl instance;
            return instance;
        }

        void setup(GLFWwindow* currentContext);
        void updateFrame();
        void renderFrame();

    private:
        Imgui_Impl() = default;
        ~Imgui_Impl();
    };
}

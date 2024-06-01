#pragma once

#include <cstdint>
#include <vector>
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Quirk::Engine::Display
{
    struct DisplayWindow
    {
    public:
        DisplayWindow(uint32_t width, uint32_t height, const char* title);
        ~DisplayWindow() = default;

    public:
        GLFWwindow* handle;
    };
}
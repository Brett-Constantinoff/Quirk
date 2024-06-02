#pragma once

#include <cstdint>
#include <string>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "../core/Defines.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Display
{
    struct DisplayWindow
    {
    public:
        DisplayWindow(qUint32 width, qUint32 height, const std::string_view& title);
        ~DisplayWindow() = default;

    public:
        GLFWwindow* handle{ nullptr };
    };
}
#pragma once

#include <cstdint>
#include <string>
#include <vector>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/Defines.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Display
{
    struct DisplayWindow
    {
    public:
        DisplayWindow(qUint32 width, qUint32 height, const std::string_view& title);
        ~DisplayWindow() = default;

        void calculateProjectionMatrix(float width, float height);

    public:
        GLFWwindow* handle{ nullptr };
        glm::mat4 projectionMatrix{ 1.0f };
    };
}
#pragma once

#include <cstdint>
#include <string>
#include <vector>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/eventSystem/events/WindowResizeEvent.hpp"

using namespace Quirk::Engine::Core::EventSystem;
using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Display
{
    struct DisplayWindow
    {
    public:
        DisplayWindow() = default;
        ~DisplayWindow() = default;

        // have an init so we dont doubly initialize the window in WindowManager.cpp
        void init(uint32_t width, uint32_t height, const std::string_view& title);
        void calculateProjectionMatrix(const WindowResizeEvent& event);

    public:
        GLFWwindow* handle{ nullptr };
        glm::mat4 projectionMatrix{ 1.0f };
    };
} // namespace Quirk::Engine::Display

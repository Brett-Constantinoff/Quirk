#include "DisplayWindow.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Display
{
    DisplayWindow::DisplayWindow(qUint32 width, qUint32 height, const std::string_view& title) 
    {
        handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (!handle)
            Core::Utils::Exit("Failed to create window");

        calculateProjectionMatrix(width, height);
    }

    void DisplayWindow::calculateProjectionMatrix(float width, float height)
    {
        // these are all default values for the time being, fov, near and far should be fine as is
        projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    }
}


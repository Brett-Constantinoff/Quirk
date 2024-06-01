#include "DisplayWindow.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Display
{
    DisplayWindow::DisplayWindow(uint32_t width, uint32_t height, const char* title) :
        handle(nullptr)
    {
        handle = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!handle)
            Core::Utils::Exit("Failed to create window");
    }
}


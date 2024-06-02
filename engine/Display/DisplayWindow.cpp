#include "DisplayWindow.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Display
{
    DisplayWindow::DisplayWindow(qUint32 width, qUint32 height, const std::string_view& title) 
    {
        handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (!handle)
            Core::Utils::Exit("Failed to create window");
    }
}


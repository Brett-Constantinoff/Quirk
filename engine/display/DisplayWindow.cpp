#include "../core/eventSystem/EventBus.hpp"
#include "../core/eventSystem/events/KeyPressEvent.hpp"

#include "DisplayWindow.hpp"

namespace Quirk::Engine::Display
{
    DisplayWindow::DisplayWindow(uint32_t width, uint32_t height, const std::string_view& title) 
    {
        handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (!handle)
            quirkExit("Failed to create window");

        // we calculate the projection matrix here, as it is a one time thing when the window is created
        // the other calculations are done in the event handler
        projectionMatrix = glm::perspective(glm::radians(45.0f), (float) width/ height, 0.1f, 100.0f);

        // subscribe to a resize event to recalculate the projection matrix
        EventBus::subscribe<DisplayWindow, WindowResizeEvent>(this, &DisplayWindow::calculateProjectionMatrix);
            
        // we fire an event on the window, and have the display manager listen for the event
        glfwSetKeyCallback(handle,
            [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
            {
                if (static_cast<KeyAction>(action) == KeyAction::KeyPress)
                    EventBus::publish(KeyPressEvent(key, action));
            });
    }

    void DisplayWindow::calculateProjectionMatrix(const WindowResizeEvent& event)
    {
        const glm::vec2 dimensions{ event.getDim()};
        // these are all default values for the time being, fov, near and far should be fine as is
        projectionMatrix = glm::perspective(glm::radians(45.0f), dimensions.x / dimensions.y, 0.1f, 100.0f);
    }
}

#include "DisplayWindow.hpp"

#include "../core/utils/Utils.hpp"
#include "../core/eventSystem/EventBus.hpp"
#include "../core/eventSystem/events/KeyPressEvent.hpp"

using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Core::EventSystem;
using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Display
{
    DisplayWindow::DisplayWindow(qUint32 width, qUint32 height, const std::string_view& title) 
    {
        handle = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
        if (!handle)
            quirkExit("Failed to create window");

        calculateProjectionMatrix(width, height);

        // we fire an event on the window, and have the display manager listen for the event
        glfwSetKeyCallback(handle,
            [](GLFWwindow* window, qInt32 key, qInt32 scancode, qInt32 action, qInt32 mods)
            {
                if (static_cast<KeyAction>(action) == KeyAction::KeyPress)
                    EventBus::publish(KeyPressEvent(key, action));
            });
    }

    void DisplayWindow::calculateProjectionMatrix(float width, float height)
    {
        // these are all default values for the time being, fov, near and far should be fine as is
        projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
    }
}

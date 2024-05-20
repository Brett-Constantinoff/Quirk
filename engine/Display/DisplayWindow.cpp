#include "DisplayWindow.hpp"
#include "../core/Engine.hpp"

namespace Quirk::Engine::Display
{
    DisplayWindow::DisplayWindow(): m_window(nullptr)
    {
    }
    
    void DisplayWindow::init(uint32_t width, uint32_t height, const char* title)
    {
        if(glfwInit() != GLFW_TRUE)
            Core::Utils::Exit("Failed to initialize GLFW");

        // tell glfw not to create an opengl context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // vulkan handles window rezising itself
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if(!m_window)
        {
            Core::Utils::Exit("Failed to create window");
        }
    }
    
    void DisplayWindow::cleanup() const
    {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
    
    GLFWwindow* DisplayWindow::get() const
    {
        return m_window;
    }

    std::vector<const char*> DisplayWindow::getExtensions() const
    {
        uint32_t count{};
        const char** extensions{ glfwGetRequiredInstanceExtensions(&count) };
    
        std::vector<const char*> extensionNames(extensions, extensions + count);
        
        if (m_enableValidationLayers)
            extensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        
        return extensionNames;
    }
}


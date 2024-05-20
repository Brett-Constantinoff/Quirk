#pragma once
#include <cstdint>
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <vector>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32

namespace Quirk::Engine::Display
{
    class DisplayWindow
    {
    public:
        DisplayWindow();
        ~DisplayWindow() = default;

        void init(uint32_t width, uint32_t height, const char* title);
        void cleanup() const;

        GLFWwindow* get() const;

        std::vector<const char*> getExtensions() const;
        inline bool shouldClose() const
        {
            return glfwWindowShouldClose(m_window);
        }

        

    private:
        GLFWwindow* m_window;

        //TODO: maybe transfer this to a global file. 
#ifdef DEBUG
        const bool m_enableValidationLayers{ true };
#else
        const bool m_enableValidationLayers{ false };
#endif // DEBUG
    };
}
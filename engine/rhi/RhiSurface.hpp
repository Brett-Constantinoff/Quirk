#pragma once

#include "../Display/DisplayWindow.hpp"

namespace Quirk::Engine::Rhi
{
    class RhiValidation;

    class RhiSurface
    {
    public:
        RhiSurface() :
            m_surface{ VK_NULL_HANDLE }
        {
        }

        ~RhiSurface() = default;

        inline void init(const VkInstance& instance, const Display::DisplayWindow& window)
        {
            if (glfwCreateWindowSurface(instance, window.get(), nullptr, &m_surface) != VK_SUCCESS)
            {
                Core::Utils::Exit("Failed to create window surface");
            }
        }

        inline void cleanup(const VkInstance& instance) const
        {
            vkDestroySurfaceKHR(instance, m_surface, nullptr);
        }


        inline VkSurfaceKHR& get()
        {
            return m_surface;
        }

    private:
        VkSurfaceKHR m_surface;
    };
}
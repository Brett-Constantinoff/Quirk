#include "RhiSurface.hpp"

#include "RhiValidation.hpp"
#include "../core/Utils.hpp"


namespace Quirk::Engine::Rhi
{
    RhiSurface::RhiSurface () : m_surface{ VK_NULL_HANDLE }
    {
    }
    
    void RhiSurface::init(const VkInstance& instance, const Display::DisplayWindow& window)
    {
        if(glfwCreateWindowSurface(instance, window.get(), nullptr, &m_surface) != VK_SUCCESS)
        {
            Core::Utils::Exit("Failed to create window surface");
        }
    }
    
    void RhiSurface::cleanup(const VkInstance& instance) const
    {
        vkDestroySurfaceKHR(instance, m_surface, nullptr);
    }
    
    VkSurfaceKHR& RhiSurface::get()
    {
        return m_surface;
    }
    
    
}


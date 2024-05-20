#pragma once

#include "../Display/DisplayWindow.hpp"

namespace Quirk::Engine::Rhi
{
    class RhiValidation;

    class RhiSurface
    {
    public:
        RhiSurface();
        ~RhiSurface() = default;

        void init(const VkInstance& instance, const Display::DisplayWindow& window);
        void cleanup(const VkInstance& instance) const;

        VkSurfaceKHR& get();

        static std::vector<const char*> getExtensions(const RhiValidation& validation);

    private:
        VkSurfaceKHR m_surface;
    };
}
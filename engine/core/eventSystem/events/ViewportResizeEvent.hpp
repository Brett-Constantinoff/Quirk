#pragma once
#include <glm/glm.hpp>

#include "../../utils/Defines.hpp"

#include "Event.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem::Events
{
    class ViewportResizeEvent : public Event
    {
    public:
        ViewportResizeEvent(const glm::vec2& dim, float aspectRatio = NULL);

        glm::vec2 getDim() const;
        float getAspectRatio() const;

    private:
        glm::vec2 m_dim;
        float m_aspectRatio;
    };
}
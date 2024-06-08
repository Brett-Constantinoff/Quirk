#pragma once 

#include <glm/glm.hpp>

#include "../../utils/Defines.hpp"

#include "Event.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem::Events
{
    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(const glm::vec2& dim);

        glm::vec2 getDim() const;

    private:
        glm::vec2 m_dim;
    };
}

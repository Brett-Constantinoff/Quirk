#include "WindowResizeEvent.hpp"

namespace Quirk::Engine::Core::EventSystem::Events
{
    WindowResizeEvent::WindowResizeEvent(const glm::vec2& dim) :
        m_dim{ dim }
    {
        m_type = EventType::WindowResize;
    }

    glm::vec2 WindowResizeEvent::getDim() const 
    { 
        return m_dim; 
    }
} // namespace Quirk::Engine::Core::EventSystem::Events

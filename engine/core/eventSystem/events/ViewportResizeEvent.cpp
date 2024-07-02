#include "ViewportResizeEvent.hpp"

namespace Quirk::Engine::Core::EventSystem::Events
{
    ViewportResizeEvent::ViewportResizeEvent(const glm::vec2& dim) :
        m_dim{ dim }
    {
        m_type = EventType::ViewportResize;
    }

    glm::vec2 ViewportResizeEvent::getDim() const 
    { 
        return m_dim; 
    }
}

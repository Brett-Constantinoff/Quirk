#include "ViewportResizeEvent.hpp"

namespace Quirk::Engine::Core::EventSystem::Events
{
    ViewportResizeEvent::ViewportResizeEvent(const glm::vec2& dim, float aspectRatio) :
        m_dim{ dim }, m_aspectRatio{ aspectRatio }
    {
        m_type = EventType::ViewportResize;
    }

    glm::vec2 ViewportResizeEvent::getDim() const 
    { 
        return m_dim; 
    }

    float ViewportResizeEvent::getAspectRatio() const
    {
        return m_aspectRatio;
    }
}

#include "KeyPressEvent.hpp"

namespace Quirk::Engine::Core::EventSystem::Events
{
    KeyPressEvent::KeyPressEvent(int32_t key, int32_t action) :
        m_key{ static_cast<KeyType>(key) },
        m_action{ static_cast<KeyAction>(action) }
    {
        m_type = EventType::KeyPress;
    }

    KeyType KeyPressEvent::getKey() const 
    {
        return m_key; 
    }

    KeyAction KeyPressEvent::getAction() const 
    { 
        return m_action; 
    }
}

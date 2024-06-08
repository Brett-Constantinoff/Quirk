#pragma once

#include "../../utils/Defines.hpp"

#include "Event.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem::Events
{
    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(int32_t key, int32_t action);

        KeyType getKey() const;
        KeyAction getAction() const;

    private:
        KeyType m_key;
        KeyAction m_action;
    };
}

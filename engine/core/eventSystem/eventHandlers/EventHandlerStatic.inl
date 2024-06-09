#pragma once

#include "EventHandlerStatic.hpp"

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    template<typename EventType>
    inline EventHandlerStatic<EventType>::EventHandlerStatic(void (*staticFunction)(const EventType&))
        : staticFunction{ staticFunction }
    {
    }

    template<typename EventType>
    inline void EventHandlerStatic<EventType>::call(const Event& event)
    {
        staticFunction(static_cast<const EventType&>(event));
    }
}

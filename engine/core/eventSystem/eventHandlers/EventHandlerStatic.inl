#pragma once

#include "EventHandlerStatic.hpp"

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    template<typename EventType>
    EventHandlerStatic<EventType>::EventHandlerStatic(void (*staticFunction)(const EventType&))
        : staticFunction{ staticFunction }
    {
    }

    template<typename EventType>
    void EventHandlerStatic<EventType>::call(const Event& event)
    {
        staticFunction(static_cast<const EventType&>(event));
    }
}

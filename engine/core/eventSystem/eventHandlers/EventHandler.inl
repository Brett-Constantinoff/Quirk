#pragma once

#include "EventHandler.hpp"

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    template<class T, class EventType>
    EventHandler<T, EventType>::EventHandler(T& instance, void (T::* memberFunction)(const EventType&))
        :   instance{ instance }, 
            memberFunction{ memberFunction }
    {
    }

    template<class T, class EventType>
    void EventHandler<T, EventType>::call(const Event& event)
    {
        const EventType& specificEvent = static_cast<const EventType&>(event);
        (instance.*memberFunction)(specificEvent);
    }
}

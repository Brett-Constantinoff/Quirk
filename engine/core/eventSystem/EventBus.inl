#pragma once

#include "EventBus.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem
{
    template<typename EventType>
    static void EventBus::publish(const EventType& event)
    {
        auto it{ eventSubscribers.find(typeid(EventType)) };

        if (it == eventSubscribers.end() || !it->second)
            return;

        std::list<EventHandlerBase*>& handlers{ *(it->second) };

        for (const auto& handler : handlers)
        {
            if (handler == nullptr)
                continue;

            handler->execute(event);

            if (event.handled())
                break;
        }

        if (!event.handled())
            spdlog::error("There was an unhandled event of type: {}", mapEventType(event.getType()));
    }

    template<class T, class EventType>
    static void EventBus::subscribe(T* instance, void (T::* MemberFunction)(const EventType&))
    {
        auto& handlers{ eventSubscribers[typeid(EventType)] };

        if (!handlers)
            handlers = std::make_unique<std::list<EventHandlerBase*>>();

        handlers->push_back(new EventHandler<T, EventType>{ *instance, MemberFunction });
    }

    template<typename EventType>
    static void EventBus::subscribe(void (*StaticFunction)(const EventType&))
    {
        auto& handlers{ eventSubscribers[typeid(EventType)] };

        if (!handlers)
            handlers = std::make_unique<std::list<EventHandlerBase*>>();

        handlers->push_back(new EventHandlerStatic<EventType>{ StaticFunction });
    }
}

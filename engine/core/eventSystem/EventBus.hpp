#pragma once

#include <list>
#include <memory>
#include <typeindex>
#include <map>

#include <spdlog/spdlog.h>

#include "../../core/utils/Utils.hpp"

#include "EventHandler.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem
{
    class EventBus
    {
    public:
        template<typename EventType>
        static void publish(const EventType& event)
        {
            auto it = eventSubscribers.find(typeid(EventType));

            if (it == eventSubscribers.end() || !it->second)
                return;

            std::list<EventHandlerBase*>& handlers = *(it->second);

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

        // the order the events are published is the order they are subscribed
        // so if A subscribes before B, A will be called before B
        template<class T, class EventType>
        static void subscribe(T* instance, void (T::* MemberFunction)(const EventType&))
        {
            auto& handlers = eventSubscribers[typeid(EventType)];

            if (!handlers)
                handlers = std::make_unique<std::list<EventHandlerBase*>>();

            handlers->push_back(new EventHandler<T, EventType>{ *instance, MemberFunction });
        }

        template<typename EventType>
        static void subscribe(void (*StaticFunction)(const EventType&))
        {
            auto& handlers = eventSubscribers[typeid(EventType)];

            if (!handlers)
                handlers = std::make_unique<std::list<EventHandlerBase*>>();

            handlers->push_back(new EventHandlerStatic<EventType>{ StaticFunction });
        }

    private:
        inline static std::map<std::type_index, std::unique_ptr<std::list<EventHandlerBase*>>> eventSubscribers{};
    };
}

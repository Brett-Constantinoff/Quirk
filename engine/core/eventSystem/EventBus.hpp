#pragma once

#include <list>
#include <memory>
#include <typeindex>
#include <map>

#include <spdlog/spdlog.h>

#include "../../core/utils/Utils.hpp"

#include "eventHandlers/EventHandlerBase.hpp"
#include "eventHandlers/EventHandler.hpp"
#include "eventHandlers/EventHandlerStatic.hpp"

using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Core::EventSystem::EventHandlers;

namespace Quirk::Engine::Core::EventSystem
{
    class EventBus
    {
    public:
        template<typename EventType>
        static void publish(const EventType& event);

        // the order the events are published is the reverse order they are subscribed
        // so if A subscribes before B, B will be called before A
        template<class T, class EventType>
        static void subscribe(T* instance, void (T::* MemberFunction)(const EventType&));
       
        template<typename EventType>
        static void subscribe(void (*StaticFunction)(const EventType&));
      
    private:
        inline static std::map<std::type_index, std::unique_ptr<std::list<EventHandlerBase*>>> eventSubscribers{};
    };
}

#include "EventBus.inl"
#pragma once

#include "../events/Event.hpp"
#include "EventHandlerBase.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    template<typename EventType>
    class EventHandlerStatic : public EventHandlerBase
    {
    public:
        EventHandlerStatic(void (*staticFunction)(const EventType&));

        void call(const Event& event) override;

    private:
        void (*staticFunction)(const EventType&);
    };
}

#include "EventHandlerStatic.inl"
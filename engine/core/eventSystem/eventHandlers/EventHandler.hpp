#pragma once

#include "../events/Event.hpp"
#include "EventHandlerBase.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    template<class T, class EventType>
    class EventHandler : public EventHandlerBase
    {
    public:
        // take in an instance of the class and a member function to wrap
        EventHandler(T& instance, void (T::* memberFunction)(const EventType&));

        // call the member function on the instance
        void call(const Event& event) override;

    private:
        T& instance;
        void (T::* memberFunction)(const EventType&);
    };
}

#include "EventHandler.inl"
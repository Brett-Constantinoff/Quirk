#pragma once

#include "events/Event.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::EventSystem
{
    class EventHandlerBase
    {
    public:
        virtual ~EventHandlerBase() = default;

        void execute(const Event& event)
        {
            call(event);
        }

    private:
        // let each event handler implement this
        virtual void call(const Event& event) = 0;
    };

    template<class T, class EventType>
    class EventHandler : public EventHandlerBase
    {
    public:
        // take in an instance of the class and a member function to wrap
        EventHandler(T& instance, void (T::* memberFunction)(const EventType&)) :
            instance{ instance },
            memberFunction{ memberFunction }
        {
        }

        // call the member function on the instance
        void call(const Event& event) override
        {
            (instance.*memberFunction)(static_cast<const EventType&>(event));
        }

    private:
        T& instance;
        void (T::* memberFunction)(const EventType&);
    };

    template<typename EventType>
    class EventHandlerStatic : public EventHandlerBase
    {
    public:
        EventHandlerStatic(void (*staticFunction)(const EventType&))
            : staticFunction(staticFunction) {}

        void call(const Event& event) override
        {
            staticFunction(static_cast<const EventType&>(event));
        }

    private:
        void (*staticFunction)(const EventType&);
    };
}

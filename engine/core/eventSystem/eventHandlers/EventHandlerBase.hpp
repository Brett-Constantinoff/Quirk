#pragma once

#include "../events/Event.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    class EventHandlerBase
    {
    public:
        virtual ~EventHandlerBase() = default;

        void execute(const Event& event);

    private:
        // let each event handler implement this
        virtual void call(const Event& event) = 0;
    };
}

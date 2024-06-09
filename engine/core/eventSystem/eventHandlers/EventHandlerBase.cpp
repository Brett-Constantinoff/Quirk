#include "EventHandlerBase.hpp"

namespace Quirk::Engine::Core::EventSystem::EventHandlers
{
    void EventHandlerBase::execute(const Event& event)
    {
        call(event);
    }
}
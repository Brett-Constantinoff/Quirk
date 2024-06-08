#pragma once

#include "events/Event.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::EventSystem
{
	class EventHandlerBase
	{
	public:
		void execute(Event* event)
		{
			call(event);
		}

	private:
		virtual void call(Event* event) = 0;
	};

	template<class T, class EventType>
	class EventHandler : public EventHandlerBase
	{
	public:
		typedef void (T::* MemberFunction)(EventType*);

		EventHandler(T* instance, MemberFunction memberFunction) : instance{ instance }, memberFunction{ memberFunction } {};

		void call(Event* evnt) {
			(instance->*memberFunction)(static_cast<EventType*>(evnt));
		}
	private:
		T* instance;

		MemberFunction memberFunction;
	};
}
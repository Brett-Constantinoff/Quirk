#pragma once

#include "../../utils/Defines.hpp"

#include "Event.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem::Events
{
	class KeyPressEvent : public Event
	{
	public:
		KeyPressEvent(int key, int action)
		{
			m_key = static_cast<KeyType>(key);
			m_action = static_cast<KeyAction>(action);
		}

		KeyType getKey() const { return m_key; }
		KeyAction getAction() const { return m_action; }

	private:
		KeyType m_key{};
		KeyAction m_action{};
	};
}
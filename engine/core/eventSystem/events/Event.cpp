#include "Event.hpp"

namespace Quirk::Engine::Core::EventSystem::Events
{
	bool Event::handled() const 
	{ 
		return m_handled; 
	}

	void Event::setHandled() const 
	{ 
		m_handled = true; 
	}

	EventType Event::getType() const 
	{ 
		return m_type; 
	}
} // namespace Quirk::Engine::Core::EventSystem::Events
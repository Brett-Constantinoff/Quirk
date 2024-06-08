#pragma once 

#include <glm/glm.hpp>

#include "../../core/utils/Defines.hpp"
#include "Event.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Core::EventSystem::Events
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(const glm::vec2& dim) :
			m_dim{ dim }
		{
			m_type = EventType::WindowResize;
		}

		inline glm::vec2 getDim() const { return m_dim; }

	private:
		glm::vec2 m_dim{};

	};
}
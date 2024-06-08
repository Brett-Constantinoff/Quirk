#pragma once

namespace Quirk::Engine::Core::EventSystem::Events
{
	enum class EventType
	{
		None, 
		WindowResize
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		bool handled() const { return m_handled; }
		void setHandled() const { m_handled = true; }
		EventType getType() const { return m_type; }

	protected:
		mutable bool m_handled{ false };
		EventType m_type{ EventType::None };
	};
}
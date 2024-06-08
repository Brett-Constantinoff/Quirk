#pragma once

namespace Quirk::Engine::Core::EventSystem::Events
{
	enum class EventType
	{
		Unknown, 
		WindowResize,
		KeyPress,
	};

	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		bool handled() const { return m_handled; }
		void setHandled() const { m_handled = true; }
		EventType getType() const { return m_type; }

	protected:
		mutable bool m_handled{ false };
		EventType m_type{ EventType::Unknown };
	};
}
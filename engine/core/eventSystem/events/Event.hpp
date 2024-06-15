#pragma once

namespace Quirk::Engine::Core::EventSystem::Events
{
	enum class EventType
	{
		Unknown, 
		WindowResize,
		KeyPress,
		MeshCreation,
	};

	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;

		bool handled() const;
		void setHandled() const;
		EventType getType() const;

	protected:
		mutable bool m_handled{ false };
		EventType m_type{ EventType::Unknown };
	};
}
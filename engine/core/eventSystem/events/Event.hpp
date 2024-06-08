#pragma once

namespace Quirk::Engine::Core::EventSystem::Events
{
	class Event
	{
	public:
		virtual ~Event() = default;
		bool handled() const { return n_handled; }

	private:
		bool n_handled{ false };
	};
}
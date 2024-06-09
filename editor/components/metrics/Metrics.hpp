#pragma once
#include "../Component.hpp"

namespace Quirk::Editor::Components::Metrics
{
	class Metrics : public Component
	{
	public:
		Metrics() = default;
		~Metrics() override;

		virtual void render();
	};
}
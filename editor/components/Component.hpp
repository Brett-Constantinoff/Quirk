#pragma once

#include <renderer/gui/ImguiImpl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		Component() {};
		virtual ~Component() {};
		virtual void render() = 0;
	};
} // namespace Quirk::Editor::Components
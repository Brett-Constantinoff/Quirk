#pragma once

#include <renderer/gui/ImguiImpl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		virtual ~Component() {};
		virtual void render() = 0;
	};
}
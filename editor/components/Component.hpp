#pragma once

#include <renderer/gui/Imgui_Impl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		virtual ~Component() {};
		virtual void render() = 0;
	};
}
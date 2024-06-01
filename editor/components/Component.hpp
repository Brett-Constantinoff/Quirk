#pragma once

#include <gui/Imgui_Impl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		Component() {}
		virtual ~Component() {}
		virtual void render() {};
	};
}
#pragma once

#include <gui/Imgui_Impl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		/// <summary>
		/// Overridable destructor
		/// </summary>
		virtual ~Component() = 0;
		/// <summary>
		/// Overridable render function
		/// </summary>
		virtual void render() = 0;
	};
}
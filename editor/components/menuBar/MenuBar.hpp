#pragma once

#include "../Component.hpp"

namespace Quirk::Editor::Components::MenuBar
{
	class MenuBar : public Component
	{
	public:
		MenuBar();
		~MenuBar();

		virtual void render();

	private:
		void renderFileMenu();
		void renderSettingsMenu();
	};
}
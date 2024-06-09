#pragma once

#include "../Component.hpp"

namespace Quirk::Editor::Components::MenuBar
{
	class MenuBar : public Component
	{
	public:
		MenuBar() = default;
		~MenuBar() override;

		void render() override;

	private:
		void renderFileMenu();
		void renderSettingsMenu();
	};
}
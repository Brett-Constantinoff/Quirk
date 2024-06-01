#pragma once
#include <vector>
#include <memory>
#include <display/DisplayManager.hpp>

#include "../components/Component.hpp"
#include "../components/menuBar/MenuBar.hpp"

using namespace Quirk::Editor::Components;

using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Gui;

namespace Quirk::Editor
{
	class Editor
	{
	public:
		Editor();
		~Editor();

		/// <summary>
		/// Main application loop, all subsystems will 'tick' here.
		/// </summary>
		void tick();

	private:
		void setup();
		void renderEditor();

	private:
		DisplayManager m_displayManager;
		std::vector<std::unique_ptr<Components::Component>> m_components;
	};
}

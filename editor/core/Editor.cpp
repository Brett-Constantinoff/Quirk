#include "Editor.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Editor
{
	void Editor::tick()
	{
		setup();

		const auto& display{m_displayManager->getWindow(DisplayTypes::Default)};
		while (!m_displayManager->windowsShouldClose())
		{
			m_renderer->tick();
			renderEditor();
			m_displayManager->tick(DisplayTypes::Default);
		}
	}

	void Editor::setup()
	{
		// load initial settings
		ApplicationSettings::getInstance().loadDefaults();

		// setup our subsystems
		m_displayManager = std::make_unique<DisplayManager>();
		m_renderer = std::make_unique<Renderer>();

		// TODO - It would be cool to time this to see how long it takes
		{
			m_displayManager->init();
			m_renderer->init();
		}

		// setup our gui
		Imgui_Impl::getInstance().setup(m_displayManager->getWindow(DisplayTypes::Default).handle);
		m_components.push_back(std::make_unique<MenuBar::MenuBar>());
	}

	void Editor::renderEditor()
	{
		Imgui_Impl::getInstance().updateFrame();

		for (auto& component : m_components)
			component->render();

		Imgui_Impl::getInstance().renderFrame();
	}
}
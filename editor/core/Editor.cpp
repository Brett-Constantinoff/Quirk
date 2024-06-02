#include <core/Utils.hpp>

#include "Editor.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Editor
{
	void Editor::tick()
	{
		setup();

		double lastFrame{ Utils::GetTime() };

		const auto& display{m_displayManager->getWindow(DisplayTypes::Default)};
		while (!m_displayManager->windowsShouldClose())
		{
			const double currFrame{ Utils::GetTime() };
			const double tickSpeed{ currFrame - lastFrame };
			lastFrame = currFrame;

			m_renderer->tick(tickSpeed, display);
			renderEditor();
			m_displayManager->tick(DisplayTypes::Default, tickSpeed);
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

			// this comes after we init the renderer so we can get the appropriate 
			// opengl version for setting up windows
			m_displayManager->initWindows();
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
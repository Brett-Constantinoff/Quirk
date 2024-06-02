#include <core/utils/Utils.hpp>
#include <renderer/gui/Imgui_Impl.hpp>

#include "Editor.hpp"

namespace Quirk::Editor
{
	void Editor::tick()
	{
		setup();

		double lastFrame{ CoreUtils::GetTime() };

		const auto& display{DisplayManager::getWindow(DisplayTypes::Default)};
		while (DisplayManager::windowsShouldClose())
		{
			const double currFrame{ CoreUtils::GetTime() };
			const double tickSpeed{ currFrame - lastFrame };
			lastFrame = currFrame;

			Renderer::tick(tickSpeed, display);
			renderEditor();
			DisplayManager::tick(DisplayTypes::Default, tickSpeed);
		}
	}

	void Editor::setup()
	{
		// load initial settings
		ApplicationSettings::loadDefaults();

		// TODO - It would be cool to time this to see how long it takes
		{
			DisplayManager::init();
			Renderer::init();

			// this comes after we init the renderer so we can get the appropriate 
			// opengl version for setting up windows
			DisplayManager::initWindows();
		}

		// setup our gui
		Gui::Imgui_Impl::setup(DisplayManager::getWindow(DisplayTypes::Default).handle);
		m_components.push_back(std::make_unique<MenuBar::MenuBar>());
	}

	void Editor::renderEditor()
	{
		Gui::Imgui_Impl::updateFrame();

		for (auto& component : m_components)
			component->render();

		Gui::Imgui_Impl::renderFrame();
	}
}
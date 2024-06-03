#include <core/utils/Utils.hpp>
#include <core/utils/Timer.hpp>
#include <renderer/gui/Imgui_Impl.hpp>

#include "Editor.hpp"

namespace Quirk::Editor
{
	void Editor::tick()
	{
		setup();

		double lastFrame{ getTime() };

		const auto& display{DisplayManager::getWindow(DisplayTypes::Default)};
		while (DisplayManager::windowsShouldClose())
		{
			const double currFrame{ getTime() };
			const double tickSpeed{ currFrame - lastFrame };
			lastFrame = currFrame;

			Renderer::tick(tickSpeed, display);
			renderEditor();
			DisplayManager::tick(DisplayTypes::Default, tickSpeed);
		}
	}

	void Editor::shutDown()
	{
		Gui::Imgui_Impl::shutdown();
		DisplayManager::shutDown();
		Renderer::shutDown();

		for (auto& component : m_components)
			delete component;
	}

	void Editor::setup()
	{
		Timer::start();
		{
			// load initial settings
			ApplicationSettings::loadDefaults();

			DisplayManager::init();
			Renderer::init();

			// this comes after we init the renderer so we can get the appropriate 
			// opengl version for setting up windows
			DisplayManager::initWindows();

			// setup our gui
			Gui::Imgui_Impl::init(DisplayManager::getWindow(DisplayTypes::Default).handle);
			m_components.emplace_back(new MenuBar::MenuBar);
		}
		spdlog::info("Quirk Setup took: {}ms", Timer::stop());
	}

	void Editor::renderEditor()
	{
		Gui::Imgui_Impl::updateFrame();

		for (auto& component : m_components)
			component->render();

		Gui::Imgui_Impl::renderFrame();
	}
}
#include <core/utils/Utils.hpp>
#include <core/utils/Timer.hpp>
#include <renderer/gui/ImguiImpl.hpp>

#include "Editor.hpp"

namespace Quirk::Editor
{
	void Editor::run()
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
			Gui::ImguiImpl::init(DisplayManager::getWindow(DisplayTypes::Default).handle);

			m_components.emplace_back(new MenuBar::MenuBar);
			m_components.emplace_back(new Metrics::Metrics);
		}
		spdlog::info("Quirk Setup took: {}ms", Timer::stop());
	}

	void Editor::renderEditor()
	{
		Gui::ImguiImpl::updateFrame();

		for (std::size_t i{}; i < m_components.size(); ++i)
			m_components[i]->render();

		Gui::ImguiImpl::renderFrame();
	}
}
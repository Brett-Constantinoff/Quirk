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

			Renderer::tick(tickSpeed, display, SceneManager::getCurrentScene());
			renderEditor();
			DisplayManager::tick(DisplayTypes::Default, tickSpeed);
		}
	}

	void Editor::shutdown()
	{
		Gui::ImguiImpl::shutdown();
		SceneManager::shutdown();
		Renderer::shutdown();
		DisplayManager::shutdown();
	}

	void Editor::setup()
	{
		Timer timer;
		timer.start();
		{
			ApplicationSettings::loadDefaults();

			DisplayManager::init();
			Renderer::init();

			SceneManager::loadDefaultScene();
			Renderer::initSceneData(SceneManager::getCurrentScene());

			// this comes after we init the renderer so we can get the appropriate 
			// opengl version for setting up windows
			DisplayManager::initWindows();

			Gui::ImguiImpl::init(DisplayManager::getWindow(DisplayTypes::Default).handle);
		}
		spdlog::info("Quirk Setup took: {}ms", timer.stop());
	}

	void Editor::renderEditor()
	{
		Gui::ImguiImpl::updateFrame();
		renderComponents();
		Gui::ImguiImpl::renderFrame();
	}

	void Editor::renderComponents()
	{
		m_menuBar.render();
		m_metrics.render();
	}
}
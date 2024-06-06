#include "DisplayManager.hpp"

namespace Quirk::Engine::Display
{
	void DisplayManager::init()
	{
		const auto& settings{ AppSettings::getSettings() };
		initGlfw(settings);
		createDefaultWindow(settings);
	}

	void DisplayManager::shutDown()
	{
		glfwTerminate();
		for (const auto& window : m_windows)
			glfwDestroyWindow(window.second->handle);
	}

	void DisplayManager::initWindows()
	{
		const auto& settings{ AppSettings::getSettings() };
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void DisplayManager::tick(DisplayTypes type, double tickSpeed)
	{
		const auto& window = m_windows[type];

		glfwSwapBuffers(window->handle);
		glfwPollEvents();
	}

	bool DisplayManager::windowsShouldClose()
	{
		// this is just checking for the default window for now
		// we will need an event system to handle multiple windows
		return !glfwWindowShouldClose(m_windows[DisplayTypes::Default]->handle);
	}

	void DisplayManager::initGlfw(const SettingsObject& settings)
	{
		if (glfwInit() != GLFW_TRUE)
			quirkExit("Failed to initialize GLFW");
	}

	void DisplayManager::createDefaultWindow(const SettingsObject& settings)
	{
		m_windows.insert({ DisplayTypes::Default, std::make_unique<DisplayWindow>(settings.windowWidth, settings.windowHeight,
			settings.windowTitle) });
		setCurrentContext(DisplayTypes::Default);
	}
}


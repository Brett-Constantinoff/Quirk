#include "DisplayManager.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Display
{
	DisplayManager::~DisplayManager()
	{
		glfwTerminate();
		for (const auto& window : m_windows)
			glfwDestroyWindow(window.second->handle);
	}

	void DisplayManager::init()
	{
		const auto& settings{ Core::ApplicationSettings::getInstance().getSettings() };
		initGlfw(settings);
		createDefaultWindow(settings);
	}

	void DisplayManager::tick(DisplayTypes type)
	{
		const auto& window = m_windows[type];

		glfwSwapBuffers(window->handle);
		glfwPollEvents();
	}

	bool DisplayManager::windowsShouldClose()
	{
		// TODO - this is just checking ALL windows, so if the
		// user closes one, all will close (if we have more than one
		for (const auto& window : m_windows)
			if (!glfwWindowShouldClose(window.second->handle))
				return false;
		return true;
	}

	void DisplayManager::initGlfw(const SettingsObject& settings)
	{
		if (glfwInit() != GLFW_TRUE)
			Utils::Exit("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, settings.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, settings.minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void DisplayManager::createDefaultWindow(const SettingsObject& settings)
	{
		auto defaultWindow = std::make_shared<DisplayWindow>(settings.windowWidth, settings.windowHeight,
			settings.windowTitle);
		m_windows.insert({ DisplayTypes::Default, defaultWindow });
		setCurrentContext(DisplayTypes::Default);
	}
}


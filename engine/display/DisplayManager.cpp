#include <glm/glm.hpp>

#include "DisplayManager.hpp"

namespace Quirk::Engine::Display
{
	void DisplayManager::init()
	{
		const auto& settings{ AppSettings::getSettings() };
		initGlfw(settings);
		createDefaultWindow(settings);

		// subscribe to any events
		EventBus::subscribe<KeyPressEvent>(&DisplayManager::handleWindowInput);
	}

	void DisplayManager::shutdown()
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

	DisplayWindow DisplayManager::getWindow(DisplayTypes type) 
	{ 
		return *m_windows[type]; 
	}

	void DisplayManager::tick(DisplayTypes type, double tickSpeed)
	{
		const auto& window = m_windows[type];

		glfwSwapBuffers(window->handle);
		glfwPollEvents();
	}

	void DisplayManager::setCurrentContext(DisplayTypes type) 
	{ 
		return glfwMakeContextCurrent(m_windows[type]->handle); 
	}

	bool DisplayManager::windowsShouldClose()
	{
		// this is just checking for the default window for now
		// we will need an event system to handle multiple windows
		return !glfwWindowShouldClose(m_windows[DisplayTypes::Default]->handle);
	}

	void DisplayManager::handleWindowInput(const KeyPressEvent& event)
	{
		if (event.getKey() == KeyType::Esc && event.getAction() == KeyAction::KeyPress)
		{
			glfwSetWindowShouldClose(m_windows[DisplayTypes::Default]->handle, GLFW_TRUE);
			event.setHandled();
		}
	}

	void DisplayManager::initGlfw(const SettingsObject& settings)
	{
		if (glfwInit() != GLFW_TRUE)
			quirkExit("Failed to initialize GLFW");
	}

	void DisplayManager::createDefaultWindow(const SettingsObject& settings)
	{
		m_defaultWindow.init(settings.windowWidth, settings.windowHeight, settings.windowTitle);

		m_windows.insert({ DisplayTypes::Default, &m_defaultWindow });
		setCurrentContext(DisplayTypes::Default);

		glfwSetFramebufferSizeCallback(m_windows[DisplayTypes::Default]->handle,
			[](GLFWwindow* window, int32_t width, int32_t height)
		{
				// create a window resize event, any subscribers will be notified
				EventBus::publish(WindowResizeEvent(glm::vec2 { width, height }));
		});
	}
}


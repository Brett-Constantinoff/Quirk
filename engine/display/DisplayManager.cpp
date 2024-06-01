#include "DisplayManager.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Display
{
	DisplayManager::DisplayManager()
	{
		initGlfw();
		createDefaultWindow();
		initGlad();
	}

	DisplayManager::~DisplayManager()
	{
		glfwTerminate();
		for (const auto& window : m_windows)
			glfwDestroyWindow(window.second->handle);
	}

	void DisplayManager::windowTick(DisplayTypes type)
	{
		const auto& window = m_windows[type];

		glfwPollEvents();
		glfwSwapBuffers(window->handle);

		// TODO - This could be moved to the renderer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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

	void DisplayManager::initGlfw()
	{
		if (glfwInit() != GLFW_TRUE)
			Utils::Exit("Failed to initialize GLFW");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	void DisplayManager::initGlad()
	{
		// TODO - This could be moved to a different class in the future
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			Utils::Exit("Failed to initialize Glad");
	}

	void DisplayManager::createDefaultWindow()
	{
		// TODO - this data could me read from a config file
		auto defaultWindow = std::make_shared<DisplayWindow>(1200, 800, "Quirk Engine");
		m_windows.insert({ DisplayTypes::Default, defaultWindow });
		setCurrentContext(DisplayTypes::Default);
	}
}


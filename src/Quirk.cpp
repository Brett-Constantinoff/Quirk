#include "Quirk.hpp"

Quirk::Quirk()
{
	init();
}

Quirk::~Quirk()
{
	clean();
}

void Quirk::run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
	}
}

void Quirk::init()
{
	initWindow();
}

void Quirk::clean()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Quirk::initWindow()
{
	// need to init glfw library before we can use it
	if (glfwInit() != GLFW_TRUE)
		exit(EXIT_FAILURE);

	// tell glfw not to create an opengl context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	// vulkan handles window rezising itself
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// creates our window handle
	m_window = glfwCreateWindow(m_width, m_height, m_appName, nullptr, nullptr);
}

void Quirk::initVulkan()
{

}
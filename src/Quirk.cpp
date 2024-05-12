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
	initVulkan();
}

void Quirk::clean()
{
	vkDestroyInstance(m_instance, nullptr);
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
	/*/
	Create a Vulkan instance
	*/
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = m_appName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	// we need an extension to interface with the window system
	uint32_t glfwExtensions{ 0 };
	const char** glfwExtensionNames{ glfwGetRequiredInstanceExtensions(&glfwExtensions) };
	createInfo.enabledExtensionCount = glfwExtensions;
	createInfo.ppEnabledExtensionNames = glfwExtensionNames;

	// validation layers will be added later
	createInfo.enabledLayerCount = 0;

	VkResult result{ vkCreateInstance(&createInfo, nullptr, &m_instance) };
	if (result != VK_SUCCESS)
		exit(EXIT_FAILURE);
}
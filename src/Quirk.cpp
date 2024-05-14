#include "Quirk.hpp"

Quirk::Quirk()
{
	initWindow();
	initVulkan();
}

Quirk::~Quirk()
{
	//NOTE - things are destroyed in reverse order of creation
	if (m_enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);

	vkDestroyInstance(m_instance, nullptr);
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Quirk::run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
	}
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
	createInstance();

	/*
	Setup debugging
	*/
	if (m_enableValidationLayers)
		createDebugMessenger();

	/*
	Pick a physical device
	*/
	pickPhysicalDevice();
}

void Quirk::createDebugMessenger()
{
	VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	populateDebugMessengerCreateInfo(createInfo);

	if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS)
		exit(EXIT_FAILURE);
}

void Quirk::pickPhysicalDevice()
{
	VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};

	uint32_t deviceCount{};
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);

	if (deviceCount == 0)
	{
		spdlog::error("failed to find GPUs with Vulkan support!");
		exit(EXIT_FAILURE);
	}


	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());

	for (const auto& device : devices)
	{
		if (isDeviceSuitable(device))
		{
			physicalDevice = device;
			break;
		}
	}

	if (physicalDevice == VK_NULL_HANDLE)
	{
		spdlog::error("failed to find a suitable GPU!");
		exit(EXIT_FAILURE);
	}
}

void Quirk::createInstance()
{
	// first check for validation layer support
	if (m_enableValidationLayers && !checkValidationLayerSupport())
		exit(EXIT_FAILURE);

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
	const auto extensions{ getExtensions() };
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();

	// add our validation layers if we are in debug mode
	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	if (m_enableValidationLayers)
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
		createInfo.ppEnabledLayerNames = m_validationLayers.data();

		populateDebugMessengerCreateInfo(debugCreateInfo);
		createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	}
	else
		createInfo.enabledLayerCount = 0;

	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
		exit(EXIT_FAILURE);
}

bool Quirk::checkValidationLayerSupport()
{
	uint32_t count{};
	vkEnumerateInstanceLayerProperties(&count, nullptr);

	std::vector<VkLayerProperties> availableLayers(count);
	vkEnumerateInstanceLayerProperties(&count, availableLayers.data());

	const uint32_t max{ 2048 };
	for (const auto layerName : m_validationLayers)
	{
		bool layerFound{ false };

		for (const auto& layerProperties : availableLayers)
		{
			if (strncmp(layerName, layerProperties.layerName, max) == 0)
			{
				layerFound = true;
				break;
			}
		}

		if (!layerFound)
			return false;
	}

	return true;
}

std::vector<const char*> Quirk::getExtensions() const
{
	uint32_t count{};
	const char** extensions{ glfwGetRequiredInstanceExtensions(&count) };

	std::vector<const char*> extensionNames(extensions, extensions + count);

	if (m_enableValidationLayers) 
		extensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

	return extensionNames;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Quirk::debugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	VkDebugUtilsMessageTypeFlagsEXT messageType,
	const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData) 
{
	switch (messageSeverity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
		spdlog::trace("validation layer: {}", pCallbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
		spdlog::info("validation layer: {}", pCallbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
		spdlog::warn("validation layer: {}", pCallbackData->pMessage);
		break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
		spdlog::error("validation layer: {}", pCallbackData->pMessage);
		break;
	}
	return VK_FALSE;
}

VkResult Quirk::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
{
	auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	return func != nullptr ? 
		func(instance, pCreateInfo, pAllocator, pDebugMessenger) :
		VK_ERROR_EXTENSION_NOT_PRESENT;
}

void Quirk::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
{
	auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	if (func != nullptr) 
		func(instance, debugMessenger, pAllocator);
}

void Quirk::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo)
{
	/*
	Setup debugging
	*/
	debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;

	// these are the types of messages we want to receive / log 
	debugCreateInfo.messageSeverity =
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

	// we want all message types to be logged
	debugCreateInfo.messageType =
		VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
		VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	debugCreateInfo.pfnUserCallback = debugCallback;
	debugCreateInfo.pUserData = nullptr;
}

bool Quirk::isDeviceSuitable(const VkPhysicalDevice &device)
{
	QueueFamilyIndices indices = findQueueFamilies(device);
	return indices.isComplete();
}

QueueFamilyIndices Quirk::findQueueFamilies(const VkPhysicalDevice &device)
{
	QueueFamilyIndices indices {};

	uint32_t queueFamilyCount {};
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int32_t i {};
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}

		if (indices.isComplete())
			break;
		

		i++;
	}
	
	return indices;
}

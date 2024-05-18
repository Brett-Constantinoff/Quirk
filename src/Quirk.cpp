#include "Quirk.hpp"

Quirk::Quirk()
{
	initWindow();
	initVulkan();
}

Quirk::~Quirk()
{
	//NOTE - things are destroyed in reverse order of creation

	for (const auto imageView : m_swapChainImageViews) 
		vkDestroyImageView(m_device, imageView, nullptr);
	
	vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);

	vkDestroyDevice(m_device, nullptr);

	if (m_enableValidationLayers)
		DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);

	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
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
	Create our window surface
	*/
	createSurface();

	/*
	Pick a physical device
	*/
	pickPhysicalDevice();

	/*
	Creates our logical device
	*/
	createLogicalDevice();

	/*
	* Create our swapchain
	*/
	createSwapChain();

	/*
	Create our image views
	*/
	createImageViews();
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
	m_physDevice = VK_NULL_HANDLE;

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
			m_physDevice = device;
			break;
		}
	}

	if (m_physDevice == VK_NULL_HANDLE)
	{
		spdlog::error("failed to find a suitable GPU!");
		exit(EXIT_FAILURE);
	}
}

void Quirk::createLogicalDevice()
{
	const auto indices{ findQueueFamilies(m_physDevice) };

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
	std::set<uint32_t> uniqueQueueFamilies{ indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };

	const float queuePriority{ 1.0f };
	for (const auto queueFamily : uniqueQueueFamilies)
	{
		VkDeviceQueueCreateInfo queueCreateInfo{};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures{};

	VkDeviceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();

	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(m_deviceExtentions.size());
	createInfo.ppEnabledExtensionNames = m_deviceExtentions.data();

	if (m_enableValidationLayers) 
	{
		createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
		createInfo.ppEnabledLayerNames = m_validationLayers.data();
	}
	else 
		createInfo.enabledLayerCount = 0;

	if (vkCreateDevice(m_physDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS)
		exit(EXIT_FAILURE);

	vkGetDeviceQueue(m_device, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);
	vkGetDeviceQueue(m_device, indices.m_presentFamily.value(), 0, &m_presentQueue);
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

void Quirk::createSurface()
{
	if (glfwCreateWindowSurface(m_instance, m_window, nullptr, &m_surface) != VK_SUCCESS)
		exit(EXIT_FAILURE);
}

void Quirk::createSwapChain()
{
	const SwapChainDetails swapChainSupport{ querySwapChainSupport(m_physDevice) };

	const VkSurfaceFormatKHR surfaceFormat{ chooseSwapSurfaceFormat(swapChainSupport.m_formats) };
	const VkPresentModeKHR presentMode{ chooseSwapPresentMode(swapChainSupport.m_presentModes) };
	const VkExtent2D extent{ chooseSwapExtent(swapChainSupport.m_capabilities) };

	// should request 1 more than the minimum (just a standard)
	uint32_t imageCount{ swapChainSupport.m_capabilities.minImageCount + 1 };

	if (swapChainSupport.m_capabilities.maxImageCount > 0 && imageCount > swapChainSupport.m_capabilities.maxImageCount) 
		imageCount = swapChainSupport.m_capabilities.maxImageCount;
	
	VkSwapchainCreateInfoKHR createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = m_surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;

	// were saying we want to render directly to the image
	// TODO - this is a temporary solution, in the future we could use this for post processing
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	QueueFamilyIndices indices = findQueueFamilies(m_physDevice);
	uint32_t queueFamilyIndices[] = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };

	if (indices.m_graphicsFamily != indices.m_presentFamily) 
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else 
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	createInfo.preTransform = swapChainSupport.m_capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	
	// TODO - This will need to change if we want to resize the window
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
		exit(EXIT_FAILURE);

	vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);

	m_swapChainImages.resize(imageCount);

	vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());

	m_swapChainImageFormat = surfaceFormat.format;
	m_swapChainExtent = extent;
}

void Quirk::createImageViews()
{
	m_swapChainImageViews.resize(m_swapChainImages.size());

	for (size_t i{}; i < m_swapChainImages.size(); i++)
	{
		VkImageViewCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = m_swapChainImages[i];
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_swapChainImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(m_device, &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
			exit(EXIT_FAILURE);
	}
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
	bool extensionsSupported = checkDeviceExtensionSupport(device);

	bool swapChainAdequate{ false };
	if (extensionsSupported) 
	{
		SwapChainDetails swapChainSupport{ querySwapChainSupport(device) };
		swapChainAdequate = !swapChainSupport.m_formats.empty() && !swapChainSupport.m_presentModes.empty();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

QueueFamilyIndices Quirk::findQueueFamilies(const VkPhysicalDevice &device)
{
	QueueFamilyIndices indices {};

	uint32_t queueFamilyCount {};
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

	int32_t i {};
	for (const auto& queueFamily : queueFamilies) 
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
			indices.m_graphicsFamily = i;

		// our device needs to be able to present to our window surface
		VkBool32 presentSupport{ false };
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

		if (indices.isComplete())
			break;
		
		if (presentSupport)
			indices.m_presentFamily = i;

		i++;
	}
	
	return indices;
}

bool Quirk::checkDeviceExtensionSupport(const VkPhysicalDevice& device)
{
	uint32_t count{};
	vkEnumerateDeviceExtensionProperties(device, nullptr, &count, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(count);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &count, availableExtensions.data());

	std::set<std::string> requiredExtensions(m_deviceExtentions.begin(), m_deviceExtentions.end());

	for (const auto& extension : availableExtensions)
		requiredExtensions.erase(extension.extensionName);

	return requiredExtensions.empty();
}

SwapChainDetails Quirk::querySwapChainSupport(const VkPhysicalDevice& device)
{
	SwapChainDetails details{};

	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, m_surface, &details.m_capabilities);

	uint32_t formatCount{};
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);

	if (formatCount != 0)
	{
		details.m_formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.m_formats.data());
	}

	uint32_t presentModeCount{};
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);

	if (presentModeCount != 0)
	{
		details.m_presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.m_presentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR Quirk::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	for (const auto& availableFormat : availableFormats)
	{
		const bool isSrgb{ availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB };
		const bool isLinear{ availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

		// TODO - this is a temporary solution, in the future we could rank the formats based on how well they match our requirements
		// this will be fine for now though
		if (isSrgb && isLinear)
			return availableFormat;
	}

	// if we can't find a format that matches our requirements, just return the first one
	return availableFormats[0];
}

VkPresentModeKHR Quirk::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		// sweet sweet triple buffering
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			return availablePresentMode;
	}

	// This is our fallback mode, it's guaranteed to be supported
	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D Quirk::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX)
		return capabilities.currentExtent;

	int32_t width{};
	int32_t height{};

	glfwGetFramebufferSize(m_window, &width, &height);

	VkExtent2D actualExtent{ static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

	// need to set the width and height to be within the min and max extents
	actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
	actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

	return actualExtent;
}

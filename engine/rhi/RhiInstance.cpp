#include "RhiInstance.hpp"

namespace Quirk::Engine::Rhi
{
	RhiInstance::RhiInstance() :
		m_instance{ VK_NULL_HANDLE },
		m_validation{},
		m_appName{"Quirk"}
	{
	}

	RhiInstance::~RhiInstance()
	{
	}

	void RhiInstance::init()
	{
		// first check for validation layer support
		if (m_validation.enableValidationLayers() && !m_validation.checkValidationLayerSupport())
			Core::Utils::Exit("validation layers requested, but not available!");

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
		auto layers{ m_validation.getValidationLayers() };

		if (m_validation.enableValidationLayers())
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
			createInfo.ppEnabledLayerNames = layers.data();

			m_validation.populateDebugMessengerCreateInfo(debugCreateInfo);
			createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
		}
		else
			createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS)
			Core::Utils::Exit("failed to create instance");

		if (!m_validation.enableValidationLayers()) return;

		if (m_validation.CreateDebugUtilsMessengerEXT(m_instance, &debugCreateInfo, nullptr, &m_validation.getDebugMessenger()) != VK_SUCCESS)
			Core::Utils::Exit("failed to create debug messenger");
	}

	// TODO - this shouldnt be here instead it should probably be with the windowing system
	std::vector<const char*> RhiInstance::getExtensions()
	{
		uint32_t count{};
		const char** extensions{ glfwGetRequiredInstanceExtensions(&count) };

		std::vector<const char*> extensionNames(extensions, extensions + count);

		if (m_validation.enableValidationLayers())
			extensionNames.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		return extensionNames;
	}
}

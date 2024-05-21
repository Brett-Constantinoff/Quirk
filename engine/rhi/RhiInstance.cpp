#include "RhiInstance.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Rhi
{
	void RhiInstance::init(const Display::DisplayWindow& window)
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
		const auto extensions{ window.getExtensions() };
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
}

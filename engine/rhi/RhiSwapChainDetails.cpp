#include "RhiSwapChainDetails.hpp"

namespace Quirk::Engine::Rhi
{
	
	SwapChainDetails RhiSwapChainDetails::querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		SwapChainDetails details{};

		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.m_capabilities);

		uint32_t formatCount{};
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.m_formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.m_formats.data());
		}

		uint32_t presentModeCount{};
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.m_presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.m_presentModes.data());
		}

		return details;
	}
}

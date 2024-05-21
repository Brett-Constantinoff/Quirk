#include <vector>

#include "RhiQueueFamilies.hpp"

namespace Quirk::Engine::Rhi
{
	QueueFamilyIndices& RhiQueueFamilies::findQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
	{
		if (isComplete())
			return m_indices;

		uint32_t queueFamilyCount{};
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		int32_t i{};
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				m_indices.m_graphicsFamily = i;

			// our device needs to be able to present to our window surface
			VkBool32 presentSupport{ false };
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			if (isComplete())
				break;

			if (presentSupport)
				m_indices.m_presentFamily = i;

			i++;
		}

		return m_indices;
	}
}
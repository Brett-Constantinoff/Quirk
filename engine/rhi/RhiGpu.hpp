#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "RhiQueueFamilies.hpp"
#include "RhiSwapChainDetails.hpp"

namespace Quirk::Engine::Rhi
{
	class RhiGpu
	{
	public:
		RhiGpu()
			: m_physDevice(VK_NULL_HANDLE)
			, m_deviceExtentions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME }
		{
		}

		~RhiGpu() = default;

		void init(const VkInstance& instance, const VkSurfaceKHR& surface);

		inline VkPhysicalDevice& get()
		{
			return m_physDevice;
		}

		inline std::vector<const char*>& getExtensions()
		{
			return m_deviceExtentions;
		}

	private:
		inline bool isDeviceSuitable(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
		{
			RhiQueueFamilies::get().findQueueFamilies(device, surface);

			bool extensionsSupported = checkDeviceExtensionSupport(device, surface);

			bool swapChainAdequate{ false };
			if (extensionsSupported)
			{
				SwapChainDetails swapChainSupport{ RhiSwapChainDetails::get().querySwapChainSupport(device, surface) };
				swapChainAdequate = !swapChainSupport.m_formats.empty() && !swapChainSupport.m_presentModes.empty();
			}

			return RhiQueueFamilies::get().isComplete() && extensionsSupported && swapChainAdequate;
		}

		inline bool checkDeviceExtensionSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface)
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

	private:
		VkPhysicalDevice m_physDevice;
		std::vector<const char*> m_deviceExtentions;
	};
}
#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Quirk::Engine::Rhi
{
	struct SwapChainDetails
	{
		VkSurfaceCapabilitiesKHR m_capabilities{};
		std::vector<VkSurfaceFormatKHR> m_formats{};
		std::vector<VkPresentModeKHR> m_presentModes{};
	};

	class RhiSwapChainDetails
	{
	public:
		RhiSwapChainDetails(const RhiSwapChainDetails&) = delete;
		RhiSwapChainDetails& operator=(const RhiSwapChainDetails&) = delete;

		static RhiSwapChainDetails& get()
		{
			static RhiSwapChainDetails instance;
			return instance;
		}

		SwapChainDetails querySwapChainSupport(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

	private:
		RhiSwapChainDetails() :
			m_details{}
		{
		}

		~RhiSwapChainDetails() = default;

		SwapChainDetails m_details;
	};
}

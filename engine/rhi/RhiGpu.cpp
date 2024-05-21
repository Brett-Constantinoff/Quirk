#include <set>

#include "RhiGpu.hpp"
#include "RhiSwapChainDetails.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Rhi
{
	void RhiGpu::init(const VkInstance& instance, const VkSurfaceKHR& surface)
	{
		uint32_t deviceCount{};
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		if (deviceCount == 0)
			Core::Utils::Exit("No gpus found");

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		for (const auto& device : devices)
		{
			if (isDeviceSuitable(device, surface))
			{
				m_physDevice = device;
				break;
			}
		}

		if (m_physDevice == VK_NULL_HANDLE)
			Core::Utils::Exit("No adequate physical device found");
	}
}
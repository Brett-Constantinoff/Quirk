#pragma once

#include <vulkan/vulkan.h>
#include <optional>
#include <mutex>

namespace Quirk::Engine::Rhi
{
	struct QueueFamilyIndices
	{
		std::optional<uint32_t> m_graphicsFamily;
		std::optional<uint32_t> m_presentFamily;
	};

	class RhiQueueFamilies
	{
	public:
		RhiQueueFamilies(const RhiQueueFamilies&) = delete;
		RhiQueueFamilies& operator=(const RhiQueueFamilies&) = delete;

		static RhiQueueFamilies& get()
		{
			static RhiQueueFamilies instance;
			return instance;
		}

		QueueFamilyIndices& findQueueFamilies(const VkPhysicalDevice& device, const VkSurfaceKHR& surface);

		inline bool isComplete() const
		{
			return m_indices.m_graphicsFamily.has_value() && m_indices.m_presentFamily.has_value();
		}

	private:
		RhiQueueFamilies() :
			m_indices{}
		{
		}

		~RhiQueueFamilies() = default;

		QueueFamilyIndices m_indices{};
	};
}

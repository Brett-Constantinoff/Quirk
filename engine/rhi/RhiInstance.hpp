#pragma once
#include <vulkan/vulkan.h>

// TODO - This will go in the windowing system
#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "RhiValidation.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Rhi
{
	/// <summary>
	/// Wrapper class for the Vulkan instance
	/// </summary>
	class RhiInstance
	{
	public:
		RhiInstance();

		~RhiInstance();

		/// <summary>
		/// Deletes the copy constructor
		/// </summary>
		/// <param name=""></param>
		RhiInstance(const RhiInstance&) = delete;

		/// <summary>
		/// Deletes the assignment operator
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		RhiInstance& operator=(const RhiInstance&) = delete;

		/// <summary>
		/// Initializes and creates the Vulkan instance
		/// </summary>
		void init();

		/// <summary>
		/// Destroys the Vulkan instance
		/// </summary>
		inline void cleanup()
		{
			if (m_validation.enableValidationLayers())
				m_validation.DestroyDebugUtilsMessengerEXT(m_instance, m_validation.getDebugMessenger(), nullptr);

			vkDestroyInstance(m_instance, nullptr);
		}

		inline VkInstance& get() 
		{ 
			return m_instance; 
		}

		// TODO - Move this into the windowing system
		std::vector<const char*> getExtensions();

	private:
		VkInstance m_instance;
		RhiValidation m_validation;

		// TODO - This seems weird to have here, maybe we could read the 
		// initialization from a config file?
		const char* m_appName;
	};
}

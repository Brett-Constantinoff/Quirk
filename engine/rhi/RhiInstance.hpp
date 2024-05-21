#pragma once
#include <vulkan/vulkan.h>
#include "RhiValidation.hpp"
#include "../Display/DisplayWindow.hpp"



namespace Quirk::Engine::Rhi
{
	/// <summary>
	/// Wrapper class for the Vulkan instance
	/// </summary>
	class RhiInstance
	{
	public:
		RhiInstance() :
			m_instance{ VK_NULL_HANDLE },
			m_validation{},
			m_appName{ "Quirk" }
		{
		}

		~RhiInstance()
		{
		}

		/// <summary>
		/// Initializes and creates the Vulkan instance
		/// </summary>
		void init(const Display::DisplayWindow& window);

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

	private:
		VkInstance m_instance;
		RhiValidation m_validation;

		// TODO - This seems weird to have here, maybe we could read the 
		// initialization from a config file?
		const char* m_appName;
	};
}

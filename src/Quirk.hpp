#pragma once

#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

struct QueueFamilyIndices {
public:
	std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		return graphicsFamily.has_value();
	}
};

class Quirk
{
public:
	/// <summary>
	/// Creates a quirk application
	/// </summary>
	Quirk();
	/// <summary>
	/// Cleans up a quirk application
	/// </summary>
	~Quirk();

	/// <summary>
	/// Main loop of the application
	/// </summary>
	void run();

private:
	/// <summary>
	/// Creates the window handle and inits glfw
	/// </summary>
	void initWindow();
	/// <summary>
	/// Creates all neccessary vulkan objects and initializes them
	/// </summary>
	void initVulkan();

/// <summary>
/// Vulkan helpers
/// </summary>
private:
	/// <summary>
	/// Creates a vulkan instance
	/// </summary>
	void createInstance();
	/// <summary>
	/// If in debug mode, creates a debug messenger
	/// </summary>
	void createDebugMessenger();
	/// <summary>
	/// Picks a physical device to use for the application
	/// </summary>
	void pickPhysicalDevice();
	/// <summary>
	/// Creates a logical device to interface with the physical device
	/// </summary>
	void createLogicalDevice();
	/// <summary>
	/// Checks to see if all requested layers are available in our
	/// validation layer vector
	/// </summary>
	/// <returns>If layers are available</returns>
	bool checkValidationLayerSupport();
	/// <summary>
	/// Gets all available extensions for the current instance
	/// </summary>
	/// <returns></returns>
	std::vector<const char*> getExtensions() const;
	/// <summary>
	/// Debug callback for vulkan
	/// </summary>
	/// <param name="messageSeverity"></param>
	/// <param name="messageType"></param>
	/// <param name="pCallbackData"></param>
	/// <param name="pUserData"></param>
	/// <returns></returns>
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);
	/// <summary>
	/// Loads the function pointer for creating the debug messenger
	/// </summary>
	/// <param name="instance"></param>
	/// <param name="pCreateInfo"></param>
	/// <param name="pAllocator"></param>
	/// <param name="pDebugMessenger"></param>
	/// <returns></returns>
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	/// <summary>
	/// Load the function to destroy the debug messenger
	/// </summary>
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
	/// <summary>
	/// Populates the debug messanger create info
	/// </summary>
	/// <param name="createInfo"></param>
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
	/// <summary>
	/// Currently checks if the device can process the commands we want to use by queue.
	/// For future refactoring refer to this: https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Physical_devices_and_queue_families#:~:text=Instead%20of%20just,that%20as%20follows%3A 
	/// </summary>
	bool isDeviceSuitable(const VkPhysicalDevice& device);
	/// <summary>
	/// Currently searches for a queue that supports graphics commands
	/// For future refactoring refer to this https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Physical_devices_and_queue_families#:~:text=to%20check%20for.-,Queue%20families,-It%20has%20been
	/// </summary>
	QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& device);

private:
	// Windowing
	GLFWwindow* m_window{};

	// Vulkan Objects
	VkInstance m_instance{};
	VkDebugUtilsMessengerEXT m_debugMessenger{};
	VkPhysicalDevice m_physDevice{};
	VkDevice m_device{};
	VkQueue m_graphicsQueue{};

	// Constants
	const uint32_t m_width{ 800 };
	const uint32_t m_height{ 600 };
	const char* m_appName{ "Quirk" };
	const std::vector<const char*> m_validationLayers{ "VK_LAYER_KHRONOS_validation" };

#ifdef DEBUG
	const bool m_enableValidationLayers{ true };
#else
	const bool m_enableValidationLayers{ false };
#endif // DEBUG

};
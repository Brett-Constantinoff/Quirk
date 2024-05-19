#pragma once

#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <cstdlib>
#include <fstream>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "spdlog/spdlog.h"

// do / while ensures that the macro can be used as a single statement
#define quirkExit(msg) do { spdlog::error(msg); exit(EXIT_FAILURE); } while (0)

struct QueueFamilyIndices {
public:
	std::optional<uint32_t> m_graphicsFamily{};
	std::optional<uint32_t> m_presentFamily{};

public:
	bool isComplete() const
	{
		return m_graphicsFamily.has_value() && m_presentFamily.has_value();
	}
};

struct SwapChainDetails 
{
	VkSurfaceCapabilitiesKHR m_capabilities{};
	std::vector<VkSurfaceFormatKHR> m_formats{};
	std::vector<VkPresentModeKHR> m_presentModes{};
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
	/// Creates a window surface for the application
	/// </summary>
	void createSurface();
	/// <summary>
	/// Creates our swap chain for the application
	/// </summary>
	void createSwapChain();
	/// <summary>
	/// Create image views for the swap chain images
	/// </summary>
	void createImageViews();
	/// <summary>
	/// Create our render pass
	/// </summary>
	void createRenderPass();
	/// <summary>
	/// Creates the graphics pipeline for the application
	/// </summary>
	void createGraphicsPipeline();
	/// <summary>
	/// Creates a frambuffer for our image views
	/// </summary>
	void createFrameBuffers();
	/// <summary>
	/// Creates a command bool for rendering
	/// </summary>
	void createCommandPool();
	/// <summary>
	/// Creates a buffer for the command pool
	/// </summary>
	void createCommandBuffer();
	/// <summary>
	/// Creates semaphores for synchronization
	/// </summary>
	void createSyncObjects();
	/// <summary>
	/// Creates a shader module from data
	/// </summary>
	/// <param name="code"></param>
	/// <returns></returns>
	VkShaderModule createShaderModule(const std::vector<char>& code);
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
	/// <summary>
	/// Checks if all required extensions needed for the device are supported
	/// </summary>
	/// <param name="device"></param>
	/// <returns></returns>
	bool checkDeviceExtensionSupport(const VkPhysicalDevice& device);
	/// <summary>
	/// Populates the swap chain details struct with the capabilities, formats, and present modes
	/// </summary>
	/// <param name="device"></param>
	/// <returns></returns>
	SwapChainDetails querySwapChainSupport(const VkPhysicalDevice& device);
	/// <summary>
	/// Chooses the best surface format for the swap chain (color depth
	/// </summary>
	/// <param name="availableFormats"></param>
	/// <returns></returns>
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	/// <summary>
	/// Choose how images are presented to the screen 
	/// </summary>
	/// <param name="availablePresentModes"></param>
	/// <returns></returns>
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
	/// <summary>
	/// Choose the resolution of the swap chain
	/// </summary>
	/// <param name="capabilities"></param>
	/// <returns></returns>
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	/// <summary>
	/// Loads a shader into memory from a file
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	std::vector<char> loadShader(const std::string& filename, const std::string& res);
	/// <summary>
	/// Compiles a shader from a file
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="res"></param>
	void compileShader(const std::string& filename, const std::string& res);
	/// <summary>
	/// Writes commands into the command buffer
	/// </summary>
	/// <param name="commandBuffer"></param>
	/// <param name="index"></param>
	void recordCommandBuffer(VkCommandBuffer& commandBuffer, uint32_t index);
	/// <summary>
	/// Draws the frame
	/// </summary>
	void draw();

private:
	// Windowing
	GLFWwindow* m_window{};

	// Vulkan Objects
	VkInstance m_instance{};
	VkDebugUtilsMessengerEXT m_debugMessenger{};
	VkPhysicalDevice m_physDevice{};
	VkDevice m_device{};
	VkQueue m_graphicsQueue{};
	VkQueue m_presentQueue{};
	VkSurfaceKHR m_surface{};
	VkSwapchainKHR m_swapChain{};
	std::vector<VkImage> m_swapChainImages{};
	VkFormat m_swapChainImageFormat{};
	VkExtent2D m_swapChainExtent{};
	std::vector<VkImageView> m_swapChainImageViews{};
	VkPipelineLayout m_pipelineLayout{};
	VkRenderPass m_renderPass{};
	VkPipeline m_graphicsPipeline{};
	std::vector<VkFramebuffer> m_swapChainFramebuffers{};
	VkCommandPool m_commandPool{};
	VkCommandBuffer m_commandBuffer{};
	VkSemaphore m_imageAvailableSemaphore{};
	VkSemaphore m_renderFinishedSemaphore{};
	VkFence m_inFlightFence{};

	// Constants
	const uint32_t m_width{ 800 };
	const uint32_t m_height{ 600 };
	const char* m_appName{ "Quirk" };
	const std::vector<const char*> m_validationLayers{ "VK_LAYER_KHRONOS_validation" };
	const std::vector<const char*> m_deviceExtentions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };

#ifdef DEBUG
	const bool m_enableValidationLayers{ true };
#else
	const bool m_enableValidationLayers{ false };
#endif // DEBUG

};
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

#include "Utils.hpp"
#include "../rhi/Rhi.hpp"

namespace Quirk::Engine::Core
{
	class Engine
	{
	public:
		/// <summary>
		/// Creates a quirk application
		/// </summary>
		Engine();
		/// <summary>
		/// Cleans up a quirk application
		/// </summary>
		~Engine();

		/// <summary>
		/// Main loop of the application
		/// </summary>
		void run();

	private:
		/// <summary>
		/// Creates all neccessary vulkan objects and initializes them
		/// </summary>
		void initVulkan();

		/// <summary>
		/// Vulkan helpers
		/// </summary>
	private:
		/// <summary>
		/// Creates a logical device to interface with the physical device
		/// </summary>
		void createLogicalDevice();
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
		//Display objects
		Display::DisplayWindow m_window{};
		
		// Rhi objects
		Rhi::RhiInstance m_instance{};
		Rhi::RhiValidation m_validation{};
		Rhi::RhiSurface m_surface{};
		Rhi::RhiGpu m_gpu{};

		// Vulkan objects 
		// TODO - abstract these into a vulkan class
		VkDevice m_device{};
		VkQueue m_graphicsQueue{};
		VkQueue m_presentQueue{};
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
	};
}

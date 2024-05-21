#include "Engine.hpp"

namespace Quirk::Engine::Core
{
	Engine::Engine()
	{
		m_window.init(800,600, "Clown engine 🤡");
		initVulkan();
	}

	Engine::~Engine()
	{
		//NOTE - things are destroyed in reverse order of creation
		vkDestroySemaphore(m_device, m_imageAvailableSemaphore, nullptr);
		vkDestroySemaphore(m_device, m_renderFinishedSemaphore, nullptr);
		vkDestroyFence(m_device, m_inFlightFence, nullptr);

		vkDestroyCommandPool(m_device, m_commandPool, nullptr);

		for (auto framebuffer : m_swapChainFramebuffers)
			vkDestroyFramebuffer(m_device, framebuffer, nullptr);

		vkDestroyPipeline(m_device, m_graphicsPipeline, nullptr);

		vkDestroyPipelineLayout(m_device, m_pipelineLayout, nullptr);

		vkDestroyRenderPass(m_device, m_renderPass, nullptr);

		for (const auto imageView : m_swapChainImageViews)
			vkDestroyImageView(m_device, imageView, nullptr);

		vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);

		vkDestroyDevice(m_device, nullptr);

		m_surface.cleanup(m_instance.get());

		m_instance.cleanup();

		m_window.cleanup();
	}

	void Engine::run()
	{
		while (!m_window.shouldClose())
		{
			glfwPollEvents();
			draw();
		}

		vkDeviceWaitIdle(m_device);
	}

	void Engine::initVulkan()
	{
		m_instance.init(m_window);
		m_surface.init(m_instance.get(), m_window);
		m_gpu.init(m_instance.get(), m_surface.get());

		createLogicalDevice();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createGraphicsPipeline();
		createFrameBuffers();
		createCommandPool();
		createCommandBuffer();
		createSyncObjects();
	}

	void Engine::createLogicalDevice()
	{
		auto& indices{Rhi::RhiQueueFamilies::get().findQueueFamilies(m_gpu.get(), m_surface.get())};

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{};
		std::set<uint32_t> uniqueQueueFamilies{ indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };

		const float queuePriority{ 1.0f };
		for (const auto queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();

		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(m_gpu.getExtensions().size());
		createInfo.ppEnabledExtensionNames = m_gpu.getExtensions().data();

		const auto validationLayers{ m_validation.getValidationLayers() };
		if (m_validation.enableValidationLayers())
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
			createInfo.enabledLayerCount = 0;

		if (vkCreateDevice(m_gpu.get(), &createInfo, nullptr, &m_device) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		vkGetDeviceQueue(m_device, indices.m_graphicsFamily.value(), 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, indices.m_presentFamily.value(), 0, &m_presentQueue);
	}

	void Engine::createSwapChain()
	{
		Rhi::SwapChainDetails swapChainSupport{ Rhi::RhiSwapChainDetails::get().querySwapChainSupport(m_gpu.get(), m_surface.get()) };

		const VkSurfaceFormatKHR surfaceFormat{ chooseSwapSurfaceFormat(swapChainSupport.m_formats) };
		const VkPresentModeKHR presentMode{ chooseSwapPresentMode(swapChainSupport.m_presentModes) };
		const VkExtent2D extent{ chooseSwapExtent(swapChainSupport.m_capabilities) };

		// should request 1 more than the minimum (just a standard)
		uint32_t imageCount{ swapChainSupport.m_capabilities.minImageCount + 1 };

		if (swapChainSupport.m_capabilities.maxImageCount > 0 && imageCount > swapChainSupport.m_capabilities.maxImageCount)
			imageCount = swapChainSupport.m_capabilities.maxImageCount;

		VkSwapchainCreateInfoKHR createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = m_surface.get();
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;

		// were saying we want to render directly to the image
		// TODO - this is a temporary solution, in the future we could use this for post processing
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		const auto& indices{ Rhi::RhiQueueFamilies::get().findQueueFamilies(m_gpu.get(), m_surface.get()) };
		uint32_t queueFamilyIndices[] = { indices.m_graphicsFamily.value(), indices.m_presentFamily.value() };

		if (indices.m_graphicsFamily != indices.m_presentFamily)
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		createInfo.preTransform = swapChainSupport.m_capabilities.currentTransform;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		// TODO - This will need to change if we want to resize the window
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);

		m_swapChainImages.resize(imageCount);

		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());

		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
	}

	void Engine::createImageViews()
	{
		m_swapChainImageViews.resize(m_swapChainImages.size());

		for (size_t i{}; i < m_swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = m_swapChainImages[i];
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			createInfo.format = m_swapChainImageFormat;

			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(m_device, &createInfo, nullptr, &m_swapChainImageViews[i]) != VK_SUCCESS)
				Core::Utils::Exit("validation layers requested, but not available!");
		}
	}

	void Engine::createRenderPass()
	{
		// we just have one color attachment for now
		VkAttachmentDescription colorAttachment{};
		colorAttachment.format = m_swapChainImageFormat;
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef{};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass{};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkRenderPassCreateInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;

		VkSubpassDependency dependency{};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.srcAccessMask = 0;
		dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		if (vkCreateRenderPass(m_device, &renderPassInfo, nullptr, &m_renderPass) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");
	}

	void Engine::createGraphicsPipeline()
	{
		// load our shaders
		const auto vertShaderCode{ loadShader("../engine/resources/shaders/shader.vert", "../engine/resources/shaders/vert.spv") };
		const auto fragShaderCode{ loadShader("../engine/resources/shaders/shader.frag", "../engine/resources/shaders/frag.spv") };

		// create the shader modules
		const auto vertShaderModule{ createShaderModule(vertShaderCode) };
		const auto fragShaderModule{ createShaderModule(fragShaderCode) };

		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		// describe our vertex input (no data since its all in vertex shader)
		VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.vertexAttributeDescriptionCount = 0;

		// describe how we want to draw our vertices
		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.scissorCount = 1;

		// create rasterizer
		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;

		// multi sampling is disabled for now
		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;


		// enable color blending (determines how the final color is calculated)
		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		// TODO - could set seom constants here if we want
		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		std::vector<VkDynamicState> dynamicStates = {
				VK_DYNAMIC_STATE_VIEWPORT,
				VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pushConstantRangeCount = 0;

		if (vkCreatePipelineLayout(m_device, &pipelineLayoutInfo, nullptr, &m_pipelineLayout) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.layout = m_pipelineLayout;
		pipelineInfo.renderPass = m_renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		if (vkCreateGraphicsPipelines(m_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_graphicsPipeline) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		vkDestroyShaderModule(m_device, fragShaderModule, nullptr);
		vkDestroyShaderModule(m_device, vertShaderModule, nullptr);
	}

	void Engine::createFrameBuffers()
	{
		m_swapChainFramebuffers.resize(m_swapChainImageViews.size());

		int32_t i{ 0 };
		for (const auto& imageView : m_swapChainImageViews)
		{
			VkImageView attachments[] = { imageView };

			VkFramebufferCreateInfo framebufferInfo{};
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = m_renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = m_swapChainExtent.width;
			framebufferInfo.height = m_swapChainExtent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(m_device, &framebufferInfo, nullptr, &m_swapChainFramebuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to create framebuffer!");

			i++;
		}
	}

	void Engine::createCommandPool()
	{
		const auto& indices{Rhi::RhiQueueFamilies::get().findQueueFamilies(m_gpu.get(), m_surface.get())};

		VkCommandPoolCreateInfo poolInfo{};
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = indices.m_graphicsFamily.value();

		if (vkCreateCommandPool(m_device, &poolInfo, nullptr, &m_commandPool) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");
	}

	void Engine::createCommandBuffer()
	{
		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = m_commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(m_device, &allocInfo, &m_commandBuffer) != VK_SUCCESS)
			throw std::runtime_error("failed to allocate command buffers!");
	}

	void Engine::createSyncObjects()
	{
		VkSemaphoreCreateInfo semaphoreInfo{};
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{};
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		if (vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_imageAvailableSemaphore) != VK_SUCCESS ||
			vkCreateSemaphore(m_device, &semaphoreInfo, nullptr, &m_renderFinishedSemaphore) != VK_SUCCESS ||
			vkCreateFence(m_device, &fenceInfo, nullptr, &m_inFlightFence) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

	}

	VkShaderModule Engine::createShaderModule(const std::vector<char>& code)
	{
		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

		VkShaderModule shaderModule;
		if (vkCreateShaderModule(m_device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		return shaderModule;
	}

	VkSurfaceFormatKHR Engine::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats)
		{
			const bool isSrgb{ availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB };
			const bool isLinear{ availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };

			// TODO - this is a temporary solution, in the future we could rank the formats based on how well they match our requirements
			// this will be fine for now though
			if (isSrgb && isLinear)
				return availableFormat;
		}

		// if we can't find a format that matches our requirements, just return the first one
		return availableFormats[0];
	}

	VkPresentModeKHR Engine::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes)
		{
			// sweet sweet triple buffering
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
				return availablePresentMode;
		}

		// This is our fallback mode, it's guaranteed to be supported
		return VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D Engine::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != UINT32_MAX)
			return capabilities.currentExtent;

		int32_t width{};
		int32_t height{};

		glfwGetFramebufferSize(m_window.get(), &width, &height);

		VkExtent2D actualExtent{ static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

		// need to set the width and height to be within the min and max extents
		actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
		actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

		return actualExtent;
	}

	std::vector<char> Engine::loadShader(const std::string& filename, const std::string& res)
	{
		// this will create a temp file in the project directory called "res"
		// which will get cleaned up at a later point
		compileShader(filename, res);

		std::ifstream file{ res, std::ios::ate | std::ios::binary };
		if (!file.is_open())
			Core::Utils::Exit("validation layers requested, but not available!");

		// classic C style file reading
		const size_t fileSize{ static_cast<size_t>(file.tellg()) };
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		// now that weve read the data, we can delete the file
		if (std::remove(res.c_str()) != 0)
			Core::Utils::Exit("validation layers requested, but not available!");

		return buffer;
	}

	void Engine::compileShader(const std::string& filename, const std::string& res)
	{
		const char* env{ "VULKAN_SDK" };
		const char* path{ std::getenv(env) };

		// wont get this far if they dont have the vulkan sdk installed but its
		// always good to check
		if (path == nullptr)
			Core::Utils::Exit("validation layers requested, but not available!");

		// compile our shaders
		// TODO - this command is platform dependent
		const std::string command{ std::string(path) + "/Bin/glslc.exe " + filename + " -o " + res };
		int32_t commandRes{ std::system(command.c_str()) };

		if (commandRes != 0)
			Core::Utils::Exit("validation layers requested, but not available!");
	}

	void Engine::recordCommandBuffer(VkCommandBuffer& commandBuffer, uint32_t index)
	{
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0;
		beginInfo.pInheritanceInfo = nullptr;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		VkRenderPassBeginInfo renderPassInfo{};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = m_renderPass;
		renderPassInfo.framebuffer = m_swapChainFramebuffers[index];

		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = m_swapChainExtent;

		VkClearValue clearColor = { {{0.1f, 0.35f, 1.0f, 1.0f}} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, m_graphicsPipeline);

		VkViewport viewport{};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = static_cast<float>(m_swapChainExtent.width);
		viewport.height = static_cast<float>(m_swapChainExtent.height);
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;
		vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

		VkRect2D scissor{};
		scissor.offset = { 0, 0 };
		scissor.extent = m_swapChainExtent;
		vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

		// DRAW!!!!!!!
		vkCmdDraw(commandBuffer, 3, 1, 0, 0);

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");
	}

	void Engine::draw()
	{
		vkWaitForFences(m_device, 1, &m_inFlightFence, VK_TRUE, UINT64_MAX);
		vkResetFences(m_device, 1, &m_inFlightFence);

		uint32_t imageIndex{};
		vkAcquireNextImageKHR(m_device, m_swapChain, UINT64_MAX, m_imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

		vkResetCommandBuffer(m_commandBuffer, 0);

		recordCommandBuffer(m_commandBuffer, imageIndex);

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

		VkSemaphore waitSemaphores[]{ m_imageAvailableSemaphore };
		VkPipelineStageFlags waitStages[]{ VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &m_commandBuffer;
		VkSemaphore signalSemaphores[]{ m_renderFinishedSemaphore };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(m_graphicsQueue, 1, &submitInfo, m_inFlightFence) != VK_SUCCESS)
			Core::Utils::Exit("validation layers requested, but not available!");

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[]{ m_swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr;

		vkQueuePresentKHR(m_presentQueue, &presentInfo);
	}

}


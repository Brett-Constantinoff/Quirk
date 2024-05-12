#pragma once

#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Quirk
{
public:
	Quirk();
	~Quirk();

	void run();

private:
	void init();
	void initWindow();
	void initVulkan();
	void clean();

private:
	GLFWwindow* m_window;
	VkInstance m_instance;

	const uint32_t m_width = 800;
	const uint32_t m_height = 600;
	const char* m_appName = "Quirk";
};
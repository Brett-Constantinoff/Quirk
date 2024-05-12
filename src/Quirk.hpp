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

	/// <summary>
	/// Main loop of the application
	/// </summary>
	void run();

private:
	/// <summary>
	/// Initializes the system (vulkan, glfw, etc)
	/// </summary>
	void init();
	/// <summary>
	/// Creates the window handle and inits glfw
	/// </summary>
	void initWindow();
	/// <summary>
	/// Creates all neccessary vulkan objects and initializes them
	/// </summary>
	void initVulkan();
	/// <summary>
	/// Cleans up all vulkan objects and glfw objects
	/// </summary>
	void clean();

private:
	GLFWwindow* m_window;
	VkInstance m_instance;

	const uint32_t m_width = 800;
	const uint32_t m_height = 600;
	const char* m_appName = "Quirk";
};
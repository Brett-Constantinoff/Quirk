#pragma once

#include <string>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "spdlog/spdlog.h"

namespace Quirk::Engine::Core::Utils
{
	/// <summary>
	/// Exit the application with a message
	/// </summary>
	/// <param name="msg"></param>
	template <typename T>
	static void quirkExit(const T& msg, int32_t status = EXIT_FAILURE)
	{
		spdlog::error(msg);
		exit(status);
	}

	static double getTime()
	{
		return glfwGetTime();
	}
};

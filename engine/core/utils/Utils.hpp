#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include "../eventSystem/events/Event.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::Utils
{
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

	static const char* mapEventType(EventType type)
	{
		switch (type)
		{
			case EventType::WindowResize:
				return "Window Resize";
		}
	}
};

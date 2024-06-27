#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <uuid.h>

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
			case EventType::KeyPress:
				return "Key Press";
			default:
				return "Unknown";
		}
	}

	static const std::wstring generateUuid()
	{
		static std::random_device rd{};

		static auto seed = [] 
		{
			std::array<int, std::mt19937::state_size> seedData{};
			std::generate(seedData.begin(), seedData.end(), std::ref(rd));
			return std::seed_seq(seedData.begin(), seedData.end());
		}();

		static std::mt19937 generator(seed);
		static uuids::uuid_random_generator gen {generator };

		return uuids::to_string<wchar_t>(gen());
	}
};
 
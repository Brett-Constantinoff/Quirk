#pragma once

#include <iostream>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <uuid.h>

#include "../eventSystem/events/Event.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::Utils
{
	// Primitive Paths
	inline const char* spherePrimitivePath{ "../engine/resources/models/sphere.obj" };
	inline const char* cubePrimitivePath{ "../engine/resources/models/cube.fbx" };
	inline const char* cylinderPrimitivePath{ "../engine/resources/models/cylinder.obj" };
	inline const char* conePrimitivePath{ "../engine/resources/models/cone.obj" };
	inline const char* torusPrimitivePath{ "../engine/resources/models/torus.obj" };

	// Shader Paths
	inline const char* basicShaderPath{ "../engine/resources/shaders/basicShader.hlsl" };

	template <typename T>
	inline void quirkExit(const T& msg, int32_t status = EXIT_FAILURE)
	{
		spdlog::error(msg);
		std::cin.get();
		exit(status);
	}

	inline double getTime()
	{
		return glfwGetTime();
	}

	inline const char* mapEventType(EventType type)
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

	inline const std::wstring generateUuid()
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
}; // namespace Quirk::Engine::Core::Utils	
 
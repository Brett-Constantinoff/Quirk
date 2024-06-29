#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include "../eventSystem/events/Event.hpp"

using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Core::Utils
{
	// Primitive Paths
	static const char* spherePrimitivePath{ "../engine/resources/models/sphere.obj" };
	static const char* cubePrimitivePath{ "../engine/resources/models/cube.fbx" };
	static const char* cylinderPrimitivePath{ "../engine/resources/models/cylinder.obj" };
	static const char* conePrimitivePath{ "../engine/resources/models/cone.obj" };
	static const char* torusPrimitivePath{ "../engine/resources/models/torus.obj" };

	// Shader Paths
	static const char* basicShaderPath{ "../engine/resources/shaders/basicShader.hlsl" };

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
};

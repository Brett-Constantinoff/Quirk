#pragma once

#include <stdint.h>

namespace Quirk::Engine::Core::Utils
{
	// These key codes are from the GLFW library
	enum class KeyType
	{
		Unkown = 0,
		Esc = 256,
	};

	enum class KeyAction
	{
		None, // 0
		KeyPress, // 1
	};
}
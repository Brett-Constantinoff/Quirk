#pragma once

#include <stdint.h>

namespace Quirk::Engine::Core::Utils
{
	// Type definitions
	using qInt8 = int8_t;
	using qInt16 = int16_t;
	using qInt32 = int32_t;
	using qInt64 = int64_t;

	using qUint8 = uint8_t;
	using qUint16 = uint16_t;
	using qUint32 = uint32_t;
	using qUint64 = uint64_t;

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
#pragma once

#include "spdlog/spdlog.h"

namespace Quirk::Engine::Core
{
	/// <summary>
	/// These are utilities that are used throughout the engine
	/// </summary>
	struct Utils
	{
	public:
		/// <summary>
		/// Exit the application with a message
		/// </summary>
		/// <param name="msg"></param>
		inline static void Exit(const char* msg, int32_t status = EXIT_FAILURE)
		{
			spdlog::error(msg);
			exit(status);
		}
	};
}
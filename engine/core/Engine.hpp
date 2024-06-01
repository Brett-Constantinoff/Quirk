#pragma once

#include "../display/DisplayManager.hpp"

#include "Utils.hpp"

using namespace Quirk::Engine::Display;

namespace Quirk::Engine::Core
{
	class Engine
	{
	public:
		/// <summary>
		/// Creates a quirk application
		/// </summary>
		Engine();
		/// <summary>
		/// Cleans up a quirk application
		/// </summary>
		~Engine();

		/// <summary>
		/// Main loop of the application
		/// </summary>
		void tick();


	private:
		DisplayManager m_displayManager;
	};
}

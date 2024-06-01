#include "Engine.hpp"

using namespace Quirk::Engine::Display;

namespace Quirk::Engine::Core
{
	Engine::Engine() :
		m_displayManager{}
	{
	}

	Engine::~Engine()
	{
	}

	void Engine::tick()
	{
		while (!m_displayManager.windowsShouldClose())
		{
			m_displayManager.windowTick(DisplayTypes::Default);
		}
	}
}


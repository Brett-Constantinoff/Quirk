#pragma once

#include <string>
#include <uuid.h>

namespace Quirk::Engine::Scene::Components
{
	struct NameComponent
	{
		std::wstring id{};
		std::string name{};
	};
}
#pragma once

#include <string>

namespace Quirk::Engine::Scene::Components
{
	struct NameComponent
	{
		// TODO - This should be a UUID
		uint32_t id{};
		std::string name{};
	};
}
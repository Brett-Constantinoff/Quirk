#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace Quirk::Engine::Scene::Components
{
	struct MaterialComponent
	{
		uint32_t materialId{};
		glm::vec4 diffuse{};
	};
} // namespace Quirk::Engine::Scene::Components
#pragma once

#include <glm/glm.hpp>

namespace Quirk::Engine::Scene::Components
{
	struct TransformComponent
	{
		glm::vec3 position{ 0.0f, 0.0f, 0.0f };
		glm::mat4 rotation{ 1.0f };
		glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

		glm::mat4 transform{ 1.0f };
	};
}
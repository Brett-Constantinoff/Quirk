#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Quirk::Engine::Scene::Components
{
	// TODO - Should probably have a model component in the future
	// since models can have multiple meshes
	struct MeshComponent
	{
		std::vector<glm::vec3> vertices{};
		std::vector<glm::vec3> normals{};
		std::vector<uint32_t> indices{};

		uint32_t vertexCount{};
		uint32_t indexCount{};

		bool isSubmitted{};
	};
} // namespace Quirk::Engine::Scene::Components

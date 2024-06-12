#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace Quirk::Engine::Renderer::Rendering
{
	struct Mesh
	{
		// vertex data
		std::vector<glm::vec3> vertices{};
		std::vector<uint32_t> indices{};
	};
}
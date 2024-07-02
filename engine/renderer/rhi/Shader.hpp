#pragma once

#include <glm/glm.hpp>

namespace Quirk::Engine::Renderer::Rhi
{
	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual uint32_t getId() = 0;
		virtual void use() = 0;
		virtual void disuse() = 0;

		virtual void setVec3(const char* name, const glm::vec3& value) = 0;
		virtual void setMat4(const char* name, const glm::mat4& matrix) = 0;
	};
} // namespace Quirk::Engine::Renderer::Rhi
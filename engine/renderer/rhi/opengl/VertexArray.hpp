#pragma once

#include <cstdint>
#include <glad/glad.h>

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray() = default;

		void bind() const;
		void unbind() const;
		uint32_t& getId();

		void setData(uint32_t size, uint32_t stride,
			GLenum type = GL_FLOAT, GLboolean normalized = false);

	private:
		uint32_t m_id{};
	};
}
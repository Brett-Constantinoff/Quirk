#pragma once

#include <glad/glad.h>

#include "../../../core/utils/Defines.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray() = default;

		void bind() const;
		void unbind() const;
		qUint32& getId();

		void setData(qUint32 size, qUint32 stride,
			GLenum type = GL_FLOAT, GLboolean normalized = false);

	private:
		qUint32 m_id{};
	};
}
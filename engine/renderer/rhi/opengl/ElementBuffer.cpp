#include <glad/glad.h>

#include "ElementBuffer.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	ElementBuffer::ElementBuffer()
	{
		glGenBuffers(1, &m_id);
	}

	void ElementBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
	}

	void ElementBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t& ElementBuffer::getId()
	{
		return m_id;
	}

	void ElementBuffer::setData(const void* data, uint32_t size) const
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}

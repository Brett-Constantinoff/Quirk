#include <glad/glad.h>

#include "VertexBuffer.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	VertexBuffer::VertexBuffer()
	{
		glGenBuffers(1, &m_id);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_id);
	}

	void VertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	uint32_t& VertexBuffer::getId()
	{
		return m_id;
	}

	void VertexBuffer::setData(const void* data, uint32_t size) const
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
}
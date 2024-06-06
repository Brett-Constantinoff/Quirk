#include "VertexArray.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_id);
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_id);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	qUint32& VertexArray::getId()
	{
		return m_id;
	}

	void VertexArray::setData(qUint32 size, qUint32 stride, GLenum type, GLboolean normalized)
	{
		glVertexAttribPointer(0, size, type, normalized, stride * sizeof(float), (void*)0);

		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, size, type, normalized, stride * sizeof(float), (void*)(size * sizeof(float)));

		glEnableVertexAttribArray(1);
	}
}
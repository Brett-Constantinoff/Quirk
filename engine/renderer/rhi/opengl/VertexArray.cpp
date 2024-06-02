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

	void VertexArray::setData(qInt32 size, float stride, GLenum type, GLboolean normalized)
	{
		const auto strideBytes{ size * m_index };

		glVertexAttribPointer(m_index, size, type, normalized, stride, (void*)strideBytes);
		glEnableVertexAttribArray(m_index);
		m_index += 1;
	}
}
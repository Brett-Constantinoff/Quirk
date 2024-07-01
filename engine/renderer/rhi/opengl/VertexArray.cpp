#include "Utils.hpp"

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

	uint32_t& VertexArray::getId()
	{
		return m_id;
	}

	void VertexArray::setData(Layout& layout) const
	{
		for (auto& attribute : layout.getAttributes())
		{
			glEnableVertexAttribArray(attribute.index);
			glVertexAttribPointer(attribute.index, attribute.size, mapTypeToGl(attribute.type),
				attribute.normalized, static_cast<GLsizei>(attribute.stride), attribute.pointer);
		}
	}
}
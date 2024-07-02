#include "OpenglLayout.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	OpenglLayout::OpenglLayout(const MeshComponent& meshComponent, const std::vector<VertexAttribute>& attribs) :
		Layout(meshComponent, attribs)
	{
	}

	OpenglLayout::~OpenglLayout()
	{
	}

	std::vector<VertexAttribute>& OpenglLayout::getAttributes()
	{
		return m_attributes;
	}

	const void* OpenglLayout::getVertexData() const
	{
		return m_meshComponent.vertices.empty() ? nullptr : m_meshComponent.vertices.data();
	}

	uint32_t OpenglLayout::getVertexDataSize() const
	{
		return m_meshComponent.vertices.empty() ? 0 : static_cast<uint32_t>(m_meshComponent.vertices.size()) * sizeof(glm::vec3);
	}

	const void* OpenglLayout::getNormalData() const
	{
		return m_meshComponent.vertices.empty() ? nullptr : m_meshComponent.vertices.data();
	}

	uint32_t OpenglLayout::getNormalDataSize() const
	{
		return m_meshComponent.normals.empty() ? 0 : static_cast<uint32_t>(m_meshComponent.normals.size()) * sizeof(glm::vec3);
	}

	const void* OpenglLayout::getIndexData() const
	{
		return m_meshComponent.indices.empty() ? nullptr : m_meshComponent.indices.data();
	}

	uint32_t OpenglLayout::getIndexDataSize() const
	{
		return m_meshComponent.indices.empty() ? 0 : static_cast<uint32_t>(m_meshComponent.indices.size()) * sizeof(uint32_t);
	}
} // namespace Quirk::Engine::Renderer::Rhi::Opengl
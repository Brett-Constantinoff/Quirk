#include "Layout.hpp"

namespace Quirk::Engine::Renderer::Rhi
{
	Layout::Layout(const MeshComponent& meshComponent, const std::vector<VertexAttribute>& attribs) :
		m_meshComponent{ meshComponent },
		m_attributes{attribs}
	{
	}
}


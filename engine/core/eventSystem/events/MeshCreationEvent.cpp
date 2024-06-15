#include "MeshCreationEvent.hpp"

namespace Quirk::Engine::Core::EventSystem::Events
{
	MeshCreationEvent::MeshCreationEvent(const std::shared_ptr<Mesh>& mesh)
		: m_mesh{mesh}
	{
		m_type = EventType::MeshCreation;
	}

	std::shared_ptr<Mesh> MeshCreationEvent::getMesh() const
	{
		return m_mesh.lock();
	}
}
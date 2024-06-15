#include "../core/eventSystem/EventBus.hpp"

#include "Scene.hpp"

namespace Quirk::Engine::Scene
{
	Scene::Scene()
	{
		EventBus::subscribe<Scene, MeshCreationEvent>(this, &Scene::onMeshCreationEvent);
	}

	void Scene::destroyActor(const Actor& actor)
	{
		m_registry.destroy(actor.getHandle());
	}

	void Scene::onMeshCreationEvent(const MeshCreationEvent& event)
	{
		auto mesh{ *event.getMesh() };
		std::shared_ptr<Actor> actor{ std::make_shared<Actor>(m_registry) };

		actor->addComponent<Mesh>(mesh);

		event.setHandled();
	}
}
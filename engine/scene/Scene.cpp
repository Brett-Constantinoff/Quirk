#include "components/TransformComponent.hpp"
#include "systems/TransformSystem.hpp"

#include "Scene.hpp"

using namespace Quirk::Engine::Scene::Components;
using namespace Quirk::Engine::Scene::Systems;

namespace Quirk::Engine::Scene
{
	std::shared_ptr<Entity>& Scene::createEntity(const std::string& name)
	{
		std::shared_ptr<Entity> entity{ std::make_shared<Entity>(m_registry) };

		NameComponent nameComponent{};
		nameComponent.name = name;

		// TODO - make a uuid
		nameComponent.id = static_cast<uint32_t>(m_entities.size());

		entity->addComponent<NameComponent>(nameComponent);
		m_entities.emplace_back(std::move(entity));

		return m_entities.back();
	}

	std::shared_ptr<Entity>& Scene::getEntity(entt::entity handle)
	{
		for (std::size_t i{0}; i < m_entities.size(); ++i)
		{
			if (m_entities[i]->getHandle() == handle)
				return m_entities[i];
		}
	}

	std::vector<std::shared_ptr<Entity>>& Scene::getEntities()
	{
		return m_entities;
	}

	void Scene::destroyEntity(const Entity& entity)
	{
		m_registry.destroy(entity.getHandle());
	}

	void Scene::tick(double tickSpeed)
	{
		glm::vec3 rotation{ 0.0f, 0.0f, 1.0f };
		const double speed{ 25.0f };

		for (const auto& entity : m_entities)
		{
			auto& transformComponent{ entity->getComponent<TransformComponent>() };
			TransformSystem::rotate(transformComponent, rotation, tickSpeed * speed);

			rotation *= -1.0f;
		}
	}
}
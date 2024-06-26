#include <uuid.h>

#include "components/TransformComponent.hpp"
#include "systems/TransformSystem.hpp"
#include "../core/utils/Utils.hpp"

#include "Scene.hpp"

using namespace Quirk::Engine::Scene::Components;
using namespace Quirk::Engine::Scene::Systems;
using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Scene
{
	std::shared_ptr<Entity>& Scene::createEntity(const std::string& name)
	{
		std::shared_ptr<Entity> entity{ std::make_shared<Entity>(m_registry) };

		NameComponent nameComponent{};
		nameComponent.name = name;

		nameComponent.id = generateUuid();

		entity->addComponent<NameComponent>(nameComponent);
		m_entities.emplace_back(std::move(entity));

		return m_entities.back();
	}

	std::shared_ptr<Entity>& Scene::getEntity(entt::entity handle)
	{
		static std::shared_ptr<Entity> entity{ nullptr };

		for (std::size_t i{ 0 }; i < m_entities.size(); ++i)
		{
			if (m_entities[i]->getHandle() == handle)
				return m_entities[i];
		}

		return entity;
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
		for (auto& entity : m_entities)
		{
			if (entity->hasComponent<TransformComponent>())
			{
				auto& transformComponent{ entity->getComponent<TransformComponent>() };
				TransformSystem::rotate(transformComponent, glm::vec3(0.0f, 1.0f, 0.0f), tickSpeed * 20.0f);
			}
		}
	}
}
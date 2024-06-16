#pragma once
#include <entt/entt.hpp>
#include <vector>

#include "components/MeshComponent.hpp"
#include "components/NameComponent.hpp"

#include "Entity.hpp"

namespace Quirk::Engine::Scene
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		[[nodiscard]] std::shared_ptr<Entity>& createEntity(const std::string& name = "Entity");
		[[nodiscard]] std::shared_ptr<Entity>& getEntity(entt::entity handle);
		void destroyEntity(const Entity& actor);
		[[nodiscard]] entt::registry& getRegistry();

	private:
		entt::registry m_registry{};
		std::vector<std::shared_ptr<Entity>> m_entities{};
	};
}
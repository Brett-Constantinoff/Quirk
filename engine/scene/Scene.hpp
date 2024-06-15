#pragma once
#include <entt/entt.hpp>
#include <vector>

#include "../core/eventSystem/events/MeshCreationEvent.hpp"

#include "Actor.hpp"

using namespace Quirk::Engine::Core::EventSystem;

namespace Quirk::Engine::Scene
{
	class Scene
	{
	public:
		Scene();
		~Scene() = default;

		void destroyActor(const Actor& actor);

		template<typename... Components>
		[[nodiscard]] inline constexpr auto view() 
		{
			return m_registry.view<Components...>();
		}

		template<typename... Components>
		[[nodiscard]] inline constexpr auto each() 
		{
			return m_registry.view<Components...>().each();
		}
		
	private:
		void onMeshCreationEvent(const MeshCreationEvent& event);

	private:
		entt::registry m_registry{};
	};
}
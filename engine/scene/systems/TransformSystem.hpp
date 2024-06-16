#pragma once

#include "../components/TransformComponent.hpp"

using namespace Quirk::Engine::Scene::Components;

namespace Quirk::Engine::Scene::Systems
{
	class TransformSystem
	{
	public:
		TransformSystem() = default;
		~TransformSystem() = default;

		static void update(TransformComponent& transformComponent);
	};
}
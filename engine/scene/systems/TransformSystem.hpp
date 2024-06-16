#pragma once

#include "../components/TransformComponent.hpp"

using namespace Quirk::Engine::Scene::Components;

namespace Quirk::Engine::Scene::Systems::TransformSystem
{
	void update(TransformComponent& transformComponent);
}
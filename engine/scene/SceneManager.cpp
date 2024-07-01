#include "../renderer/rendering/MeshFactory.hpp"
#include "../renderer/rendering/ShaderManger.hpp"
#include "../core/utils/Utils.hpp"
#include "components/MaterialComponent.hpp"
#include "components/TransformComponent.hpp"

#include "systems/TransformSystem.hpp"

#include "SceneManager.hpp"

using namespace Quirk::Engine::Renderer::Rendering;
using namespace Quirk::Engine::Scene::Systems;
using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Scene
{
	void SceneManager::init()
	{
		loadDefaultScene();
	}

	void SceneManager::shutdown()
	{
		m_scenes.clear();
	}

	void SceneManager::loadDefaultScene()
	{
		m_currentScene = std::make_shared<Scene>();
		{
			auto& entity{ m_currentScene->createEntity("Clown 1") };

			auto meshComponent{ MeshFactory::createMesh(MeshTypes::Cube, cubePrimitivePath)};
			entity->addComponent<MeshComponent>(*meshComponent);
			entity->setDrawable(true);

			MaterialComponent materialComponent{};
			materialComponent.materialId = ShaderManager::getMaterialId(MaterialType::Basic2D);
			materialComponent.diffuse = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			entity->addComponent<MaterialComponent>(materialComponent);

			TransformComponent transformComponent{};
			transformComponent.position = glm::vec3(-2.5f, 0.0f, -5.0f);
			transformComponent.scale = glm::vec3(0.5f, 0.5f, 0.5f);
			TransformSystem::update(transformComponent);

			entity->addComponent<TransformComponent>(transformComponent);
		}
		{
			auto& entity{ m_currentScene->createEntity("Clown 2") };

			auto meshComponent{ MeshFactory::createMesh(MeshTypes::Cube, cubePrimitivePath) };
			entity->addComponent<MeshComponent>(*meshComponent);
			entity->setDrawable(true);

			MaterialComponent materialComponent{};
			materialComponent.materialId = ShaderManager::getMaterialId(MaterialType::Basic2D);
			materialComponent.diffuse = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
			entity->addComponent<MaterialComponent>(materialComponent);

			TransformComponent transformComponent{};
			transformComponent.position = glm::vec3(2.5f, 0.0f, -5.0f);
			transformComponent.scale = glm::vec3(0.5f, 0.5f, 0.5f);
			TransformSystem::update(transformComponent);

			entity->addComponent<TransformComponent>(transformComponent);
		}
	}

	std::shared_ptr<Scene>& SceneManager::getCurrentScene()
	{
		return m_currentScene;
	}

	std::vector<std::shared_ptr<Scene>>& SceneManager::getScenes()
	{
		return m_scenes;
	}
}
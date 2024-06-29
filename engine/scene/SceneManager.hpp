#pragma once

#include "Scene.hpp"

namespace Quirk::Engine::Scene
{
	class SceneManager
	{
	public:
		static void init();
		static void shutdown();
		[[nodiscard]] static std::shared_ptr<Scene>& getCurrentScene();
		[[nodiscard]] static std::vector<std::shared_ptr<Scene>>& getScenes();

	private:
		static void loadDefaultScene();

	private:
		inline static std::shared_ptr<Scene> m_currentScene{ nullptr };
		inline static std::vector<std::shared_ptr<Scene>> m_scenes{};
	};
}
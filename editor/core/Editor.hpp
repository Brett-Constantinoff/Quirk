#pragma once

#include <vector>
#include <memory>

#include <display/DisplayManager.hpp>
#include <core/utils/ApplicationSettings.hpp>
#include <core/utils/Utils.hpp>
#include <renderer/rendering/Renderer.hpp>
#include <scene/SceneManager.hpp>

#include "../components/Component.hpp"
#include "../components/menuBar/MenuBar.hpp"
#include "../components/metrics/Metrics.hpp"
#include "../components/panels/MetricsPanel.hpp"
#include "../components/panels/SceneHierarchyPanel.hpp"
#include "../components/panels/ViewportPanel.hpp"

using namespace Quirk::Editor::Components;

using namespace Quirk::Engine::Core;
using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Renderer;
using namespace Quirk::Engine::Renderer::Rendering;

namespace Quirk::Editor
{
	class Editor
	{
	public:
		Editor() = default;
		~Editor() = default;

		static void run();
		static void shutdown();

	private:
		static void setup();
		static void renderEditor();
		static void renderComponents();

	private:
		//EDITOR COMPONENTS
		inline static MenuBar::MenuBar m_menuBar{};
		inline static Metrics::Metrics m_metrics{}; //TODO: Delete this
		inline static SceneHierarchyPanel m_sceneHierarchyPanel{};
		inline static MetricsPanel m_metricsPanel{};
		inline static ViewportPanel m_viewportPanel{};
	};
}

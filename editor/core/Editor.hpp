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
#include "../components/panels/ConsolePanel.hpp"
#include "../components/panels/LogPanel.hpp"
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

		static void init();
		static void run();
		static void shutdown();

	private:
		static void renderEditor();
		static void renderComponents();

	private:
		//EDITOR COMPONENTS
		inline static MenuBar::MenuBar m_menuBar;
		inline static SceneHierarchyPanel m_sceneHierarchyPanel{"Scene Hierarchy"};
		inline static MetricsPanel m_metricsPanel{"Metrics"};
		inline static ViewportPanel m_viewportPanel{"Viewport"};
		inline static ConsolePanel m_consolePanel{"Console"};
		inline static LogPanel m_logPanel{"Log"};
	};
}

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
		inline static MenuBar::MenuBar m_menuBar{};
		inline static Metrics::Metrics m_metrics{};
	};
}

#pragma once
#include <vector>
#include <memory>
#include <display/DisplayManager.hpp>
#include <core/utils/ApplicationSettings.hpp>
#include <renderer/rendering/Renderer.hpp>

#include "../components/Component.hpp"
#include "../components/menuBar/MenuBar.hpp"

using namespace Quirk::Editor::Components;

using namespace Quirk::Engine::Core;
using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Renderer;
using namespace Quirk::Engine::Renderer::Rendering;

using CoreUtils = Quirk::Engine::Core::Utils::Utils;

namespace Quirk::Editor
{
	class Editor
	{
	public:
		Editor() = default;
		~Editor() = default;

		/// <summary>
		/// Main application loop, all subsystems will 'tick' here.
		/// </summary>
		void tick();

	private:
		void setup();
		void renderEditor();

	private:
		std::vector<std::unique_ptr<Components::Component>> m_components{};
	};
}

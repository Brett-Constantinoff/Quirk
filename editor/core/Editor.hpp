#pragma once
#include <vector>
#include <memory>
#include <display/DisplayManager.hpp>
#include <core/ApplicationSettings.hpp>
#include <renderer/rendering/Renderer.hpp>

#include "../components/Component.hpp"
#include "../components/menuBar/MenuBar.hpp"

using namespace Quirk::Editor::Components;

using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Gui;
using namespace Quirk::Engine::Renderer::Rendering;

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
		std::unique_ptr<DisplayManager> m_displayManager{ nullptr };
		std::unique_ptr<Renderer> m_renderer{ nullptr };
		std::vector<std::unique_ptr<Components::Component>> m_components{};
	};
}

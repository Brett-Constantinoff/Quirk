#pragma once
#include <vector>
#include <memory>
#include <display/DisplayManager.hpp>
#include <core/utils/ApplicationSettings.hpp>
#include <core/utils/Utils.hpp>
#include <renderer/rendering/Renderer.hpp>

#include "../components/Component.hpp"
#include "../components/menuBar/MenuBar.hpp"

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
		/// <summary>
		/// Main application loop, all subsystems will 'tick' here.
		/// </summary>
		void tick();
		void shutDown();

	private:
		void setup();
		void renderEditor();

	private:
		std::vector<std::unique_ptr<Component>> m_components{};
	};
}

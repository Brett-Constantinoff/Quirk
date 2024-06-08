#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../../core/eventSystem/EventBus.hpp"
#include "../../core/eventSystem/events/WindowResizeEvent.hpp"
#include "../../display/DisplayWindow.hpp"
#include "../rhi/opengl/Opengl.hpp"
#include "../rhi/Rhi.hpp"

#include "ShaderManger.hpp"
#include "Camera.hpp"

using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Renderer::Rhi;
using namespace Quirk::Engine::Renderer::Rhi::Opengl;
using namespace Quirk::Engine::Core::EventSystem::Events;

namespace Quirk::Engine::Renderer::Rendering
{
	class Renderer
	{
	public:
		static void init();
		static void tick(double tickSpeed, const DisplayWindow& display);

	private:
		static void loadContext();
		static void chooseAndInitRhi();
		static void updateViewport(const WindowResizeEvent& event);

	private:
		 inline static Rhi::Rhi* m_rhi{ nullptr };

		 inline static Rhi::Opengl::Opengl m_opengl{};
	};
}
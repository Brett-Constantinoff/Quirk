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
		static void updateViewport(const WindowResizeEvent& event);

	private:
		 inline static std::unique_ptr<Rhi::Rhi> m_rhi{nullptr};

		 // TODO - Remove these
		 inline static Camera m_camera{};
		 inline static std::vector<float> m_data{};
	};
}
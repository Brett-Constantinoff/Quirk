#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../../display/DisplayWindow.hpp"
#include "../rhi/opengl/Opengl.hpp"
#include "../rhi/Rhi.hpp"

#include "shaders/Shader.hpp"
#include "Camera.hpp"

using namespace Quirk::Engine::Core;
using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Renderer::Rhi;
using namespace Quirk::Engine::Renderer::Rhi::Opengl;
using namespace Quirk::Engine::Renderer::Rendering::Shaders;

namespace Quirk::Engine::Renderer::Rendering
{
	class Renderer
	{
	public:
		static void init();
		static void tick(double tickSpeed, const DisplayWindow& display);
		static void shutDown();

	private:
		// depending on what backend we are using
		// we can add more here
		 inline static Rhi::Opengl::Opengl m_opengl{};
		 inline static Rhi::Rhi* m_rhi{nullptr};

		 // TODO - Remove these
		 inline static Shader* m_shader{ nullptr };
		 inline static Camera* m_camera{};
	};
}
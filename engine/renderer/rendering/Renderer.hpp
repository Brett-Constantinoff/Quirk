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
		Renderer() = default;
		~Renderer();

		void init();
		void tick(double tickSpeed, const DisplayWindow& display);

	private:
		// depending on what backend we are using
		// we can add more here
		Rhi::Opengl::Opengl m_opengl{};
		std::unique_ptr<Rhi::Rhi> m_rhi{nullptr};

		 // TODO - Remove these
		 Shader* m_shader{ nullptr };
		 Camera* m_camera{ nullptr };

		 qUint32 m_renderApi{};
		 glm::vec4 m_clearColor{};
		 bool m_clearColorBuffer{};
		 bool m_clearDepthBuffer{};
		 bool m_clearStencilBuffer{};
	};
}
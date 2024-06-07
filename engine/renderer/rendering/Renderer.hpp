#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../../display/DisplayWindow.hpp"
#include "../rhi/opengl/Opengl.hpp"
#include "../rhi/opengl/Shader.hpp"
#include "../rhi/Rhi.hpp"

#include "Camera.hpp"

using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Renderer::Rhi;
using namespace Quirk::Engine::Renderer::Rhi::Opengl;

namespace Quirk::Engine::Renderer::Rendering
{
	class Renderer
	{
	public:
		static void init();
		static void tick(double tickSpeed, const DisplayWindow& display);
		static void shutDown();

	private:
		 inline static std::unique_ptr<Rhi::Rhi> m_rhi{nullptr};

		 // TODO - Remove these
		 inline static std::unique_ptr<Shader> m_shader{ nullptr };
		 inline static std::unique_ptr<Camera> m_camera{ nullptr };
		 inline static std::vector<float> m_data{};
	};
}
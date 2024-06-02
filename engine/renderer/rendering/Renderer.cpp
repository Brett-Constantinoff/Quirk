#include "Renderer.hpp"

#include "../../core/Defines.hpp"
#include "../../core/ApplicationSettings.hpp"

using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rendering
{
	// TODO - Remove this in the future once 
	// we have a shader manager class
	Renderer::~Renderer()
	{
		delete m_shader;
	}

	void Renderer::init()
	{
		// load intial settings
		const auto& settings{ Core::ApplicationSettings::getInstance().getSettings() };

		m_renderApi = static_cast<qUint32>(settings.renderApi);
		if (m_renderApi == static_cast<qUint32>(Core::RenderApi::OpenGL))
			m_rhi = std::make_unique<Rhi::Opengl::Opengl>();

		m_clearColor = settings.clearColor;
		m_clearColorBuffer = settings.clearColorBuffer;
		m_clearDepthBuffer = settings.clearDepthBuffer;
		m_clearStencilBuffer = settings.clearStencilBuffer;

		m_rhi->init();

		// TODO - This is just here to make sure we can render something
		{
			m_shader = new Shader("../engine/resources/shaders/basicShader.hlsl");
			std::vector<float> vertices =
			{
				 0.5f,  0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,
				-0.5f,  0.5f, 0.0f
			};
			std::vector<qUint32> indices =
			{
				0, 1, 3,
				1, 2, 3
			};

			m_rhi->submitDrawData(vertices, indices, 3);
		}
	}

	void Renderer::tick()
	{
		m_rhi->clearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		m_rhi->clearBuffers(m_clearColorBuffer, m_clearDepthBuffer, m_clearStencilBuffer);

		m_shader->use();
		m_rhi->drawElements(QuirkPrimitives::Triangles, 6);
		m_shader->disuse();
	}
}

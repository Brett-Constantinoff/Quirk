#include "Renderer.hpp"

#include "../../core/Utils.hpp"
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
			m_camera = new Camera();
			std::vector<float> vertices =
			{
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
				-0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

				-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
				-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
				-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f,

				-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
				-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
				-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
				-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
				-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

				 0.5f,  0.5f,  0.5f, 0.5f, 0.25f, 0.75f,
				 0.5f,  0.5f, -0.5f, 0.5f, 0.25f, 0.75f,
				 0.5f, -0.5f, -0.5f, 0.5f, 0.25f, 0.75f,
				 0.5f, -0.5f, -0.5f, 0.5f, 0.25f, 0.75f,
				 0.5f, -0.5f,  0.5f, 0.5f, 0.25f, 0.75f,
				 0.5f,  0.5f,  0.5f, 0.5f, 0.25f, 0.75f,

				-0.5f, -0.5f, -0.5f, 0.43f, 0.68f, 0.13f,
				 0.5f, -0.5f, -0.5f, 0.43f, 0.68f, 0.13f,
				 0.5f, -0.5f,  0.5f, 0.43f, 0.68f, 0.13f,
				 0.5f, -0.5f,  0.5f, 0.43f, 0.68f, 0.13f,
				-0.5f, -0.5f,  0.5f, 0.43f, 0.68f, 0.13f,
				-0.5f, -0.5f, -0.5f, 0.43f, 0.68f, 0.13f,

				-0.5f,  0.5f, -0.5f, 0.12f, 0.24f, 0.86f,
				 0.5f,  0.5f, -0.5f, 0.12f, 0.24f, 0.86f,
				 0.5f,  0.5f,  0.5f, 0.12f, 0.24f, 0.86f,
				 0.5f,  0.5f,  0.5f, 0.12f, 0.24f, 0.86f,
				-0.5f,  0.5f,  0.5f, 0.12f, 0.24f, 0.86f,
				-0.5f,  0.5f, -0.5f, 0.12f, 0.24f, 0.86f,
			};
			m_rhi->submitDrawData(vertices, 3, 6);
		}
	}

	void Renderer::tick(double tickSpeed, const DisplayWindow& display)
	{
		m_rhi->clearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		m_rhi->clearBuffers(m_clearColorBuffer, m_clearDepthBuffer, m_clearStencilBuffer);

		constexpr double rotationAngle{ glm::radians(45.0f) };
		constexpr double damper{ 0.5f };
		const double rotationSpeed{ rotationAngle * damper * (float)Core::Utils::GetTime() };
		glm::mat4 model = glm::mat4(1.0f);
		const glm::mat4 view{ m_camera->getView() };
		const glm::mat4 projection{ display.projectionMatrix };

		constexpr glm::vec3 rotationVec{ 0.0f, 1.0f, 0.5f };

		model = glm::rotate(model, static_cast<float>(rotationSpeed), rotationVec );

		m_shader->use();

		m_shader->setMat4("uModel", model);
		m_shader->setMat4("uView", view);
		m_shader->setMat4("uProjection", projection);


		m_rhi->drawArrays(QuirkPrimitives::Triangles, 36);
		m_shader->disuse();
	}
}

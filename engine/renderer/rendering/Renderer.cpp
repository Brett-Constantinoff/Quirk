#include "Renderer.hpp"

#include "../../core/utils/Utils.hpp"
#include "../../core/utils/Defines.hpp"
#include "../../core/utils/ApplicationSettings.hpp"

#include "../utils/Context.hpp"

using namespace Quirk::Engine::Renderer::Utils;

using CoreUtils = Quirk::Engine::Core::Utils::Utils;
using AppSettings = Quirk::Engine::Core::Utils::ApplicationSettings;
using RenderApi = Quirk::Engine::Core::Utils::RenderApi;

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
		// load intial settings into our context
		const auto& settings{ AppSettings::getSettings() };

		Utils::Context::renderApi = static_cast<qUint32>(settings.renderApi);

		if (Utils::Context::renderApi == static_cast<qUint32>(RenderApi::OpenGL))
			m_rhi = std::make_unique<Rhi::Opengl::Opengl>();

		Utils::Context::clearColor = settings.clearColor;
		Utils::Context::clearColorBuffer = settings.clearColorBuffer;
		Utils::Context::clearDepthBuffer = settings.clearDepthBuffer;
		Utils::Context::clearStencilBuffer = settings.clearStencilBuffer;

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
		const auto& clearColor{ Utils::Context::clearColor };
		m_rhi->clearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		m_rhi->clearBuffers(Utils::Context::clearColorBuffer, Utils::Context::clearDepthBuffer, Utils::Context::clearStencilBuffer);

		constexpr double rotationAngle{ glm::radians(45.0f) };
		constexpr double damper{ 0.5f };
		const double rotationSpeed{ rotationAngle * damper * (float)CoreUtils::GetTime() };
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

#include "../../core/eventSystem/EventBus.hpp"
#include "../../core/utils/Utils.hpp"
#include "../../core/utils/Defines.hpp"
#include "../../core/utils/ApplicationSettings.hpp"

#include "../utils/Context.hpp"

#include "Renderer.hpp"

using namespace Quirk::Engine::Core::EventSystem;
using namespace Quirk::Engine::Renderer::Utils;

using AppSettings = Quirk::Engine::Core::Utils::ApplicationSettings;
using RenderApi = Quirk::Engine::Core::Utils::RenderApi;

namespace Quirk::Engine::Renderer::Rendering
{
	void Renderer::init()
	{
		// load intial settings into our context
		const auto& settings{ AppSettings::getSettings() };

		Utils::Context::renderApi = settings.renderApi;
		Utils::Context::clearColor = settings.clearColor;
		Utils::Context::clearColorBuffer = settings.clearColorBuffer;
		Utils::Context::clearDepthBuffer = settings.clearDepthBuffer;
		Utils::Context::clearStencilBuffer = settings.clearStencilBuffer;

		// for now just load opengl
		m_rhi = std::make_unique<Rhi::Opengl::Opengl>();
		m_rhi->init();

		// subscribe for any events
		EventBus::subscribe<WindowResizeEvent>(&Renderer::updateViewport);

		// create our materials
		ShaderManager::createMaterials();

		// TODO - This is just here to make sure we can render something
		{
			m_data =
			{
				-0.5f, -0.5f, 0.0f,
				 0.5f, -0.5f, 0.0f,
				 0.0f,  0.5f, 0.0f
			};
			m_rhi->submitDrawData(m_data, 3, 3);
		}
	}

	void Renderer::tick(double tickSpeed, const DisplayWindow& display)
	{
		const auto& basicShader{ShaderManager::getShader(MaterialType::Basic2D)};

		const auto& clearColor{ Utils::Context::clearColor };
		m_rhi->clearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		m_rhi->clearBuffers(Utils::Context::clearColorBuffer, Utils::Context::clearDepthBuffer, Utils::Context::clearStencilBuffer);

		basicShader->use();

		m_rhi->drawArrays(QuirkPrimitives::Triangles, 3);

		basicShader->disuse();
	}

	void Renderer::updateViewport(const WindowResizeEvent& event)
	{
		const glm::vec2 dimensions{ event.getDim() };
		m_rhi->setViewport(static_cast<qUint32>(dimensions.x), static_cast<qUint32>(dimensions.y));
		event.setHandled();
	}
}
